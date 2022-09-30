#include "mbed.h"
#include "arm_book_lib.h"
#include <string.h>

#include "act6.h"

#include "code.h"
#include "display.h"
#include "event_log.h"
#include "matrix_keypad.h"
#include "pc_serial_com.h"
#include "smart_home_system.h"
#include "date_and_time.h"
#include "user_interface.h"

DigitalIn Button1(D13);
DigitalIn Button2(D12);
DigitalIn Button3(D11);
DigitalIn Button4(D10);

AnalogIn AD(A0);

extern UnbufferedSerial uartUsb;
extern DigitalIn Button1;
extern DigitalIn Button2;
extern DigitalIn Button3;
extern DigitalIn Button4;

extern AnalogIn AD;

extern DigitalOut strobeLight;
extern DigitalOut incorrectCodeLed;
extern DigitalOut systemBlockedLed;

extern pcSerialComMode_t pcSerialComMode;

void buttonInit()
{
    
    Button1.mode(PullDown);
    Button2.mode(PullDown);
    Button3.mode(PullDown);
    Button4.mode(PullDown);

}

void newAvailableCommands()
{
    pcSerialComStringWrite( "Available commands:\r\n" );
    pcSerialComStringWrite( "Press '1' to activate LED1\r\n" );
    pcSerialComStringWrite( "Press '2' to activate LED2\r\n" );
    pcSerialComStringWrite( "Press '3' to activate LED3\r\n" );
    pcSerialComStringWrite( "Press '4' to show A/D value\r\n" );
    pcSerialComStringWrite( "Press other key to deactivate LEDs\r\n" );
    pcSerialComStringWrite( "\r\n" );
}

void newPcSerialComInit()
{
    newAvailableCommands();
}

void newPcSerialComCommandUpdate( char receivedChar )
{
    if( receivedChar != '\0' ) {
        switch (receivedChar) {
            
            case '1': 
                ledInit();
                strobeLight = ON;
                ThisThread::sleep_for(500ms); 
                break;
            case '2': 
                ledInit();
                systemBlockedLed = ON; 
                ThisThread::sleep_for(500ms);
                break;
            case '3': 
                ledInit();
                incorrectCodeLed = ON; 
                ThisThread::sleep_for(500ms);
                break;
            case '4': 
                ledInit();
                showAD();
                break;
            default: 
                ledInit();
                matrixKeypadUpdate(); 
                break;
        }    
    } 
}

void newPcSerialComUpdate()
{
    char receivedChar = pcSerialComCharRead();
    if( receivedChar != '\0' ) {
        switch ( pcSerialComMode ) {
            case PC_SERIAL_COMMANDS:
                newPcSerialComCommandUpdate( receivedChar );
            break;
            default:
                pcSerialComMode = PC_SERIAL_COMMANDS;
            break;
        }
    }    
}


void newUserInterfaceMatrixKeypadUpdate()
{
    char keyReleased = matrixKeypadUpdate();

    if( keyReleased != '\0' ) {
        newPcSerialComCommandUpdate( keyReleased );
        
    }
}

void ledInit(){
    strobeLight = OFF;
    systemBlockedLed = OFF; 
    incorrectCodeLed = OFF;

}

void showAD(){
    char str[50]; 

    sprintf(str, "Potentiometer value: %f\n", AD.read());
    uartUsb.write(str, strlen(str));
}

void showButton(){
    char str[20]; 
    int buttonPressed = 0;

    if (Button1.read() == ON){
        buttonPressed = 1;
    } else if (Button2.read() == ON){
        buttonPressed = 2;
    } else if (Button3.read() == ON){
        buttonPressed = 3;
    } else if (Button4.read() == ON){
        buttonPressed = 4;
    }
    thread_sleep_for(40);
    if (buttonPressed){
        sprintf(str, "Button %d pressed\n", buttonPressed );
        uartUsb.write(str, strlen(str));
    }
}
void Keyboard_LCD ()
    {
    static int accumulatedDisplayTime = 0;
    char temperatureString[3] = "";
    
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;

        static int x=0 ;
        static int y=0 ;
        displayCharPositionWrite(x,y); //@note esto lo que hace es pararme en el display en x,y
        char* key; //@note variable donde guarda lo que escribe el keypad puntero porque display string write pide punter
        *key=matrixKeypadUpdate();
        if (*key=='D'){
            x=0;
            y++;
        }
        if(*key=='C'){
            x=0;
            y=0;
        }
        displayStringWrite(key);
        x++;
    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 

}