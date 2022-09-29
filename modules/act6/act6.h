#ifndef ACT6_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define ACT6_H

void newAvailableCommands();
void newPcSerialComCommandUpdate(char receivedChar);
void newPcSerialComUpdate();
void newPcSerialComInit();
void newUserInterfaceMatrixKeypadUpdate();

void ledInit();
void showAD();
void showTM();
void showButton();

#endif