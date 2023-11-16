//Bibliotecas
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/adc.h"
#include "utils/ustdlib.h"
//Parqueos 
int p1 = 0;
int p2 = 0;
int p3 = 0;
int p4 = 0;

#define XTAL 16000000
void InitUART(void);

int main(void) {
      // Se setea oscilador externo de 16MHz
      SysCtlClockSet(
      SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

      SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
      while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)); //Esperar la inicialización del puerto
      IntMasterEnable(); //Habilitando interrupciones globales
      // Se inicializa la comunicaci n UART
      InitUART();




    // Habilitar periféricos
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);


    // Habilitar el pin de salida
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2);//LED's 1
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3);

    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6);//LED's 2
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7);

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);//LED's 3
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);//LED's 4
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);

    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_6);//Sensor 1
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_7);//Sensor 2
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_3);//Sensor 3
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_2);//Sensor 4



    while (true) {



        if (GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_6) == 0) { // Parqueo 1
                       GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0);
                       GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
                       p1 = 0B00000001;
        } else {GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2);
                GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
                      p1 = 0;}

        if (GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_7) == 0) { // Parqueo 2
                               GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);
                               GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
                               p2 = 0B00000010;
                } else {GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
                        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
                        p2 = 0;}

        if (GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_3) == 0) { // Parqueo 3
                            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);
                            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);
                            p3 = 0B00000100;
                } else {GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
                               GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
                               p3 = 0;}

        if (GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_2) == 0) { // Parqueo 4
                             GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);
                             GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
                             p4 = 0B00001000;
                } else {GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
                             GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
                             p4 = 0;}


        int parqueos = p1|p2|p3|p4;

        UARTCharPutNonBlocking(UART1_BASE, parqueos); //Enviando el byte al ESP32 por medio del UART1

    }
}

void InitUART(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1); //Habilitando el módulo UART1
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1); //Definiendo los pines para el UART
    GPIOPinConfigure(GPIO_PB0_U1RX); //Definiendo pinB0 como RX
    GPIOPinConfigure(GPIO_PB1_U1TX); //Definiendo pinB1 como TX

    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE)); //Configurando el UART1 con 115200 de baudrate, 8 bits, un dato y sin paridad
    UARTEnable(UART1_BASE); //Iniciando el UART1
}


