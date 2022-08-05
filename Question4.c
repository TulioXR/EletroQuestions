
uint8_t RX_Data;

void UART_Init(void)
{

    Set_parameters = {
        9600,   //Set baud rate
        0,      //Set parity (enable/disable)
        1,      //stop bit
        8      //bit size
    };
    
    UART_driver_install(Set_parameters);

    UART_Set_PIN(PIN_7,PIN_8);

    Enable_UART_RX_interrupt(UARTEventCallback,RX_Data);

}

void UARTEventCallback()
{
    switch (RX_Data)
    {

        case 0x00:
            /*CASE A*/
        break;

        case 0x01:
            /*CASE B*/
        break;

        case 0x02:
            /*CASE C*/
        break;
        ...

        default:
            /* MISRA Req */
        break;

    }
}

int main(void)
{
    UART_Init();

    for (;;)
    {
        sleep(100);
    }

}
