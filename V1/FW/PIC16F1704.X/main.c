#include "mcc.h"
#include "app.h"

void main(void) // <editor-fold defaultstate="collapsed" desc="Main function">
{
    SYSTEM_Initialize();
    App_Init();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    while(1)
    {
        CLRWDT();
        App_Task();
    }
} // </editor-fold>