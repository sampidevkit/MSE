/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1704
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set HONDA_LED aliases
#define HONDA_LED_TRIS                 TRISAbits.TRISA2
#define HONDA_LED_LAT                  LATAbits.LATA2
#define HONDA_LED_PORT                 PORTAbits.RA2
#define HONDA_LED_WPU                  WPUAbits.WPUA2
#define HONDA_LED_OD                   ODCONAbits.ODA2
#define HONDA_LED_ANS                  ANSELAbits.ANSA2
#define HONDA_LED_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define HONDA_LED_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define HONDA_LED_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define HONDA_LED_GetValue()           PORTAbits.RA2
#define HONDA_LED_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define HONDA_LED_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define HONDA_LED_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define HONDA_LED_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define HONDA_LED_SetPushPull()        do { ODCONAbits.ODA2 = 0; } while(0)
#define HONDA_LED_SetOpenDrain()       do { ODCONAbits.ODA2 = 1; } while(0)
#define HONDA_LED_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define HONDA_LED_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set KLINE_RX aliases
#define KLINE_RX_TRIS                 TRISAbits.TRISA4
#define KLINE_RX_LAT                  LATAbits.LATA4
#define KLINE_RX_PORT                 PORTAbits.RA4
#define KLINE_RX_WPU                  WPUAbits.WPUA4
#define KLINE_RX_OD                   ODCONAbits.ODA4
#define KLINE_RX_ANS                  ANSELAbits.ANSA4
#define KLINE_RX_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define KLINE_RX_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define KLINE_RX_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define KLINE_RX_GetValue()           PORTAbits.RA4
#define KLINE_RX_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define KLINE_RX_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define KLINE_RX_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define KLINE_RX_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define KLINE_RX_SetPushPull()        do { ODCONAbits.ODA4 = 0; } while(0)
#define KLINE_RX_SetOpenDrain()       do { ODCONAbits.ODA4 = 1; } while(0)
#define KLINE_RX_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define KLINE_RX_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set PWR_EN aliases
#define PWR_EN_TRIS                 TRISAbits.TRISA5
#define PWR_EN_LAT                  LATAbits.LATA5
#define PWR_EN_PORT                 PORTAbits.RA5
#define PWR_EN_WPU                  WPUAbits.WPUA5
#define PWR_EN_OD                   ODCONAbits.ODA5
#define PWR_EN_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define PWR_EN_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define PWR_EN_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define PWR_EN_GetValue()           PORTAbits.RA5
#define PWR_EN_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define PWR_EN_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define PWR_EN_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define PWR_EN_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define PWR_EN_SetPushPull()        do { ODCONAbits.ODA5 = 0; } while(0)
#define PWR_EN_SetOpenDrain()       do { ODCONAbits.ODA5 = 1; } while(0)

// get/set SUZUKI_LED aliases
#define SUZUKI_LED_TRIS                 TRISCbits.TRISC0
#define SUZUKI_LED_LAT                  LATCbits.LATC0
#define SUZUKI_LED_PORT                 PORTCbits.RC0
#define SUZUKI_LED_WPU                  WPUCbits.WPUC0
#define SUZUKI_LED_OD                   ODCONCbits.ODC0
#define SUZUKI_LED_ANS                  ANSELCbits.ANSC0
#define SUZUKI_LED_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define SUZUKI_LED_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define SUZUKI_LED_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define SUZUKI_LED_GetValue()           PORTCbits.RC0
#define SUZUKI_LED_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define SUZUKI_LED_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define SUZUKI_LED_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define SUZUKI_LED_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define SUZUKI_LED_SetPushPull()        do { ODCONCbits.ODC0 = 0; } while(0)
#define SUZUKI_LED_SetOpenDrain()       do { ODCONCbits.ODC0 = 1; } while(0)
#define SUZUKI_LED_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define SUZUKI_LED_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set YAMAHA_LED aliases
#define YAMAHA_LED_TRIS                 TRISCbits.TRISC1
#define YAMAHA_LED_LAT                  LATCbits.LATC1
#define YAMAHA_LED_PORT                 PORTCbits.RC1
#define YAMAHA_LED_WPU                  WPUCbits.WPUC1
#define YAMAHA_LED_OD                   ODCONCbits.ODC1
#define YAMAHA_LED_ANS                  ANSELCbits.ANSC1
#define YAMAHA_LED_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define YAMAHA_LED_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define YAMAHA_LED_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define YAMAHA_LED_GetValue()           PORTCbits.RC1
#define YAMAHA_LED_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define YAMAHA_LED_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define YAMAHA_LED_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define YAMAHA_LED_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define YAMAHA_LED_SetPushPull()        do { ODCONCbits.ODC1 = 0; } while(0)
#define YAMAHA_LED_SetOpenDrain()       do { ODCONCbits.ODC1 = 1; } while(0)
#define YAMAHA_LED_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define YAMAHA_LED_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set SPEED aliases
#define SPEED_TRIS                 TRISCbits.TRISC2
#define SPEED_LAT                  LATCbits.LATC2
#define SPEED_PORT                 PORTCbits.RC2
#define SPEED_WPU                  WPUCbits.WPUC2
#define SPEED_OD                   ODCONCbits.ODC2
#define SPEED_ANS                  ANSELCbits.ANSC2
#define SPEED_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SPEED_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SPEED_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SPEED_GetValue()           PORTCbits.RC2
#define SPEED_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SPEED_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SPEED_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define SPEED_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define SPEED_SetPushPull()        do { ODCONCbits.ODC2 = 0; } while(0)
#define SPEED_SetOpenDrain()       do { ODCONCbits.ODC2 = 1; } while(0)
#define SPEED_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define SPEED_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set PWM aliases
#define PWM_TRIS                 TRISCbits.TRISC3
#define PWM_LAT                  LATCbits.LATC3
#define PWM_PORT                 PORTCbits.RC3
#define PWM_WPU                  WPUCbits.WPUC3
#define PWM_OD                   ODCONCbits.ODC3
#define PWM_ANS                  ANSELCbits.ANSC3
#define PWM_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define PWM_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define PWM_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define PWM_GetValue()           PORTCbits.RC3
#define PWM_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define PWM_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define PWM_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define PWM_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define PWM_SetPushPull()        do { ODCONCbits.ODC3 = 0; } while(0)
#define PWM_SetOpenDrain()       do { ODCONCbits.ODC3 = 1; } while(0)
#define PWM_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define PWM_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set MODE_N aliases
#define MODE_N_TRIS                 TRISCbits.TRISC4
#define MODE_N_LAT                  LATCbits.LATC4
#define MODE_N_PORT                 PORTCbits.RC4
#define MODE_N_WPU                  WPUCbits.WPUC4
#define MODE_N_OD                   ODCONCbits.ODC4
#define MODE_N_ANS                  ANSELCbits.ANSC4
#define MODE_N_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define MODE_N_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define MODE_N_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define MODE_N_GetValue()           PORTCbits.RC4
#define MODE_N_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define MODE_N_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define MODE_N_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define MODE_N_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define MODE_N_SetPushPull()        do { ODCONCbits.ODC4 = 0; } while(0)
#define MODE_N_SetOpenDrain()       do { ODCONCbits.ODC4 = 1; } while(0)
#define MODE_N_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define MODE_N_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set KLINE_TX_N aliases
#define KLINE_TX_N_TRIS                 TRISCbits.TRISC5
#define KLINE_TX_N_LAT                  LATCbits.LATC5
#define KLINE_TX_N_PORT                 PORTCbits.RC5
#define KLINE_TX_N_WPU                  WPUCbits.WPUC5
#define KLINE_TX_N_OD                   ODCONCbits.ODC5
#define KLINE_TX_N_ANS                  ANSELCbits.ANSC5
#define KLINE_TX_N_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define KLINE_TX_N_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define KLINE_TX_N_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define KLINE_TX_N_GetValue()           PORTCbits.RC5
#define KLINE_TX_N_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define KLINE_TX_N_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define KLINE_TX_N_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define KLINE_TX_N_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define KLINE_TX_N_SetPushPull()        do { ODCONCbits.ODC5 = 0; } while(0)
#define KLINE_TX_N_SetOpenDrain()       do { ODCONCbits.ODC5 = 1; } while(0)
#define KLINE_TX_N_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define KLINE_TX_N_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/