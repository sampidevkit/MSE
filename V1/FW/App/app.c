#include "app.h"
#include "mcc.h"

#if defined(_16F15324)
#define Set_FOSC_1MHz()         OSCCON1=0x65
#define Set_FOSC_4MHz()         OSCCON1=0x63
#define Set_FOSC_32MHz()        OSCCON1=0x60
#define EUSART_RCIE             PIE3bits.RC1IE
#define EUSART_TXIE             PIE3bits.TX1IE
#define EUSART_CREN             RC1STAbits.CREN
#define EUSART_SPEN             RC1STAbits.SPEN
#define EUSART_Initialize()     EUSART1_Initialize()
#define EUSART_is_rx_ready()    EUSART1_is_rx_ready()
#define EUSART_Read()           EUSART1_Read()
#define EUSART_Write(x)         EUSART1_Write(x)
#elif defined(_16F1704)
#define Set_FOSC_1MHz()         OSCCON=0x58 // SCS FOSC; SPLLEN disabled; IRCF 1MHz_HF;
#define Set_FOSC_4MHz()         OSCCON=0x68 // SCS FOSC; SPLLEN disabled; IRCF 4MHz_HF;
#define Set_FOSC_32MHz()        do{OSCCON=0xF0; while(PLLR==0);}while(0) // SCS FOSC; SPLLEN enabled; IRCF 8MHz_HF; (FOSCx4=32MHz)
#define EUSART_RCIE             PIE1bits.RCIE
#define EUSART_TXIE             PIE1bits.TXIE
#define EUSART_CREN             RC1STAbits.CREN
#define EUSART_SPEN             RC1STAbits.SPEN
#else
#error "Your chip is not supported"
#endif

#define TICK_PER_MS                     4 // LFINTOSC/8/1000=4
#define Tick_Timer_Reset(cxt)           cxt.Over=1
#define Tick_Timer_Get()                ((((uint16_t) TMR1H)<<8)|TMR1L)
#define Tick_Timer_Is_Over_Ms(tk, t)    Tick_Timer_Is_Over(&tk, t)

typedef struct
{
    bool Over;
    uint16_t Start;
    uint16_t Duration;
} tick_timer_t;

typedef enum
{
    HONDA_MODE=0,
    SUZUKI_MODE,
    YAMAHA_MODE,
    IDLE_MODE
} mode_t;

typedef struct
{
    uint32_t alpha;
    uint32_t beta;
    uint32_t gama;
} tmr2_cxt_t;

static const tmr2_cxt_t PWMCxt[2]={
    {63, 16888, 1}, // Honda, fosc=4MHz
    {251, 67543, 4}, // Suzuki, fosc=1MHz
};

static tmr2_cxt_t *pPWMCxt;
static mode_t Mode=HONDA_MODE;
static tick_timer_t TickLed={1, 0, 0};

bool Tick_Timer_Is_Over(tick_timer_t *pTick, uint16_t ms) // <editor-fold defaultstate="collapsed" desc="Check timeout">
{
    uint16_t TMR1Val=Tick_Timer_Get();

    if(pTick->Over==1)
    {
        pTick->Start=TMR1Val;
        pTick->Duration=ms*TICK_PER_MS;
        pTick->Over=0;
    }

    if((TMR1Val-pTick->Start)>=pTick->Duration)
        pTick->Over=1;

    return pTick->Over;
} // </editor-fold>

static void KLineTx(const uint8_t *pData, uint8_t len) // <editor-fold defaultstate="collapsed" desc="K-Line Tx">
{
    EUSART_RCIE=0;
    EUSART_CREN=0; // disable RX

    while(len>0)
    {
        TX1REG=*pData; // Write the data byte to the USART.
        len--;
        pData++;
        while(0==TX1STAbits.TRMT);
    }

    EUSART_RCIE=1;
    EUSART_CREN=1; // enable RX
} // </editor-fold>

static void MODE_LED_Set(void) // <editor-fold defaultstate="collapsed" desc="Set mode LED">
{
    Tick_Timer_Reset(TickLed);

    switch(Mode)
    {
        case HONDA_MODE:
            HONDA_LED_LAT=1;
            SUZUKI_LED_LAT=0;
            YAMAHA_LED_LAT=0;
            break;

        case SUZUKI_MODE:
            HONDA_LED_LAT=0;
            SUZUKI_LED_LAT=1;
            YAMAHA_LED_LAT=0;
            break;

        case YAMAHA_MODE:
            HONDA_LED_LAT=0;
            SUZUKI_LED_LAT=0;
            YAMAHA_LED_LAT=1;
            break;

        default:
            break;
    }
} // </editor-fold>

static bool MODE_LED_Toggle(uint16_t delay) // <editor-fold defaultstate="collapsed" desc="LED toggle">
{
    if(delay>247)
    {
        MODE_LED_Set();
        Tick_Timer_Reset(TickLed);
    }

    if(Tick_Timer_Is_Over_Ms(TickLed, delay))
    {
        switch(Mode)
        {
            case HONDA_MODE:
                HONDA_LED_Toggle();
                break;

            case SUZUKI_MODE:
                SUZUKI_LED_Toggle();
                break;

            case YAMAHA_MODE:
                YAMAHA_LED_Toggle();
                break;

            default:
                break;
        }

        return 1;
    }

    return 0;
} // </editor-fold>

static uint8_t BT_MODE_Is_Pressed(void) // <editor-fold defaultstate="collapsed" desc="Check button">
{
    static uint8_t prv=1;
    static tick_timer_t Tick={1, 0, 0};

    if((prv!=2)&&(prv!=(uint8_t) MODE_N_GetValue()))
    {
        if(prv==1)
        {
            prv=0;
            Tick.Duration=1500*TICK_PER_MS;
            Tick.Start=Tick_Timer_Get();
        }
        else
        {
            prv=1;
            Tick.Duration=Tick_Timer_Get()-Tick.Start;
            Tick.Duration/=TICK_PER_MS;

            if(Tick.Duration>=50)
                return 1;
        }
    }
    else if(prv==0)
    {
        if((Tick_Timer_Get()-Tick.Start)>=Tick.Duration)
        {
            prv=2;
            return 2;
        }
    }
    else if((prv==2)&&(MODE_N_GetValue()==1))
        prv=1;

    return 0;
} // </editor-fold>

static void SPEED_Control(bool force) // <editor-fold defaultstate="collapsed" desc="Speed pulse control">
{
    static uint8_t count=0;
    static uint8_t prvAdc=0;

    uint8_t buffer[5]={0, 0, 0, 0, 0};
    uint8_t preAdc=(uint8_t) (ADC_GetConversion(SPEED)>>2); // scale down to 8-bit ADC

    if(force==1)
    {
        count=200;
        prvAdc=preAdc;
    }

    if((prvAdc!=preAdc)&&(force==0))
    {
        prvAdc=preAdc;
        count=0;
    }
    else if(count<200)
        count++;
    else if(count==200)
    {
        count=201;
        T2CONbits.TMR2ON=0;

        if(Mode<YAMAHA_MODE)
        {
            if(prvAdc<8)
                PWM4_LoadDutyValue(0);
            else
            {
                // Tpwm=beta-alpha*ADC (us)
                uint32_t tmp=prvAdc;

                tmp*=pPWMCxt->alpha;
                tmp=pPWMCxt->beta-tmp;

                // PR2=(15625/Fpwm)-1=(15625*Tpwm/1E6)-1
                tmp=15625*tmp;
                tmp/=pPWMCxt->gama;
                tmp/=1E6;
                tmp-=1;
                PR2=(uint8_t) (tmp);
                PWM4_LoadDutyValue((uint16_t) (PR2+1)<<1); // 50% duty=2*(PR2+1)
                T2CONbits.TMR2ON=1;
            }
        }
        else
            PWM4_LoadDutyValue(0);
    }

    MODE_LED_Toggle(255-prvAdc);

    if(Mode<YAMAHA_MODE)
        return;

    if(EUSART_is_rx_ready())
    {
        __delay_ms(2); // waiting time before responding

        switch(EUSART_Read()) // get command
        {
            default:
                break;

            case 0xFE:// begin transmission
                KLineTx(buffer, 5);
                break;

            case 0x01:// response
                buffer[0]=prvAdc; // rpm [0:255]
                buffer[4]=buffer[0];
                buffer[1]=prvAdc>>3; // km/h [0:31]
                buffer[4]+=buffer[1];
                buffer[2]=0x00;
                buffer[4]+=buffer[2];
                buffer[3]=0x37;
                buffer[4]+=buffer[3];
                KLineTx(buffer, 5);
                break;
        }
    }
} // </editor-fold> 

static void SYS_SpeedSet(void) // <editor-fold defaultstate="collapsed" desc="Set CPU speed">
{
    switch(Mode)
    {
        case SUZUKI_MODE:
            EUSART_RCIE=0;
            EUSART_TXIE=0;
            EUSART_SPEN=0;
            Set_FOSC_1MHz();
            break;

        case HONDA_MODE:
            EUSART_RCIE=0;
            EUSART_TXIE=0;
            EUSART_SPEN=0;
            Set_FOSC_4MHz();
            break;

        default:
            Set_FOSC_32MHz();
            EUSART_Initialize();
            break;
    }
} // </editor-fold>

void App_Init(void) // <editor-fold defaultstate="collapsed" desc="Application init">
{
    Mode=HONDA_MODE;
    MODE_LED_Set();
    SYS_SpeedSet();
    PWR_EN_SetHigh();
    pPWMCxt=(tmr2_cxt_t*)&PWMCxt[Mode];
    SPEED_Control(1);
} // </editor-fold>

void App_Task(void) // <editor-fold defaultstate="collapsed" desc="Application task">
{
    uint8_t BtEvent=BT_MODE_Is_Pressed();

    if(BtEvent==2)
    {
        bool bk=T2CONbits.TMR2ON;

        T2CONbits.TMR2ON=0;
        Mode++;

        if(Mode>YAMAHA_MODE)
            Mode=HONDA_MODE;

        MODE_LED_Set();
        SYS_SpeedSet();

        if(Mode<YAMAHA_MODE)
        {
            pPWMCxt=(tmr2_cxt_t*)&PWMCxt[Mode];
            SPEED_Control(1);
            T2CONbits.TMR2ON=bk;
        }
        else
            SPEED_Control(1);
    }
    else
    {
        if(BtEvent==1)
            PWR_EN_Toggle();

        SPEED_Control(0);
    }
} // </editor-fold>