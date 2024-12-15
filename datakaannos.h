#ifndef UART_MORSE_DECODE_H
#define UART_MORSE_DECODE_H

#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/UART.h>

#define MAX_MORSE_LEN 512

// Morse-koodi taulukko kirjaimille ja numeroille
extern char *morseCodeTable[];

// Funktiot
void morseToText(char *morseCode, char *outputText);
Void uartReceiveTaskFxn(UArg arg0, UArg arg1);

#endif // UART_MORSE_DECODE_H
