/******************************************************************************
Question 2:

Imagine a situation where you have an electronic board with a microcontroller and a button. You 
are required to check if the button is pressed (state ON) or not (state OFF) and for how long the 
button is kept pressed. If the button gets pressed, you also need to have a clear state definition 
ranging from ON, PROTECTED and OFF; as per the state diagram below. The protected state is 
defined as an intermediate stage between the transition from the ON state to the OFF state, so 
that each time the button is released, the button state changes to PROTECTED for 10 seconds 
before going to the OFF state. Implement this logic in a generic way using the C language and 
share this code through a public repository on GitHub. Low-level methods can be abstracted. If 
you prefer, use frameworks like Arduino, ESP32 or even other market platforms in this low-level 
code abstraction.


*******************************************************************************/
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"


#define DEBUG         1

#define OFF           0
#define ON            1
#define PROTECTION    2

#define LED_BOARD  GPIO_NUM_2
#define BUTTON_0      GPIO_NUM_4


void TaskMaquinaEstados( void *pvParameter )
{
    /* Local Variable */
    int state = OFF;

    /* Inicializa a GPIO para o led na placa do ESP32 */
    gpio_set_direction( LED_BOARD, GPIO_MODE_OUTPUT );
    	
    /* Inicializa a GPIO do botão do ESP32 */
    gpio_set_direction( BUTTON_0, GPIO_MODE_INPUT );
    gpio_set_pull_mode( BUTTON_0, GPIO_PULLUP_ONLY ); 
      
    for(;;) 
    {
        switch(state)
        {
            case OFF:
                if( gpio_get_level( BUTTON_0 ) == 0 )
                {
                    state = ON;
                    gpio_set_level( LED_BOARD,1);
                }
                vTaskDelay( 50/portTICK_PERIOD_MS );
            break;
            case ON:
                if( gpio_get_level( BUTTON_0 ) != 0 )
                {
                    state = PROTECTION;
                    gpio_set_level( LED_BOARD,0);
                }
                vTaskDelay( 50/portTICK_PERIOD_MS );
            break;

            case PROTECTION:
                vTaskDelay( 10000/portTICK_PERIOD_MS );
                state = OFF;
            break;

            default:
                /*MISRA Req*/
            break;
        }
    }
}

void app_main( void )
{
    xTaskCreate( TaskMaquinaEstados, "TaskMaquinaEstados", 2048, NULL, 1, NULL );

}
