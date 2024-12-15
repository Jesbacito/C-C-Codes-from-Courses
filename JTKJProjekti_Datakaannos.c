//Jessika

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>
#include <ti/drivers/UART.h>
#include <stdio.h>
#include <string.h>

#define MAX_MORSE_LEN 512

// Morse-koodi taulukko kirjaimille ja numeroille
char *morseCodeTable[] = {
    ".-",   "-...", "-.-.", "-..", ".",   "..-.", "--.",  "....", "..",   ".---", "-.-",  ".-..", "--",   "-.",   "---",  ".--.", "--.-", ".-.", "...",  "-",   "..-",  "...-", ".--",  "-..-", "-.--", "--..", // A-Z
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", // 0-9
    NULL // Tämä on taulukon loppu, joka ei ole käytettävissä
};

// Morse-koodin kääntäminen tekstiksi
void morseToText(char *morseCode, char *outputText) {
    char *token;
    char *morseCopy = strdup(morseCode);
    token = strtok(morseCopy, " "); // Pilkotaan morse-koodi sanoiksi

    while (token != NULL) {
        for (int i = 0; morseCodeTable[i] != NULL; i++) {
            if (strcmp(token, morseCodeTable[i]) == 0) {
                outputText[strlen(outputText)] = 'A' + i; // A-Z
                break;
            }
        }
        token = strtok(NULL, " ");
    }
    free(morseCopy);
}

// Morse-koodin vastaanottaminen UARTista ja kääntäminen
Void uartReceiveTaskFxn(UArg arg0, UArg arg1) {
    char receivedData[MAX_MORSE_LEN];
    char outputText[MAX_MORSE_LEN] = {0}; // Käännetty teksti
    int i = 0;

    // Alustetaan UART
    UART_Handle uart;
    UART_Params uartParams;
    UART_Params_init(&uartParams);
    uartParams.readDataMode = UART_DATA_TEXT;
    uartParams.readMode = UART_MODE_BLOCKING;
    uartParams.baudRate = 9600;
    uart = UART_open(Board_UART0, &uartParams);
    if (uart == NULL) {
        System_abort("Error opening UART\n");
    }

    while (1) {
        // Vastaanotetaan morse-koodia UARTin kautta
        int len = UART_read(uart, receivedData + i, 1); // Lue yksi merkki kerrallaan

        if (len > 0) {
            if (receivedData[i] == '\n' || receivedData[i] == '\r') {
                // Jos vastaanotettiin rivinvaihto, käsitellään saatu morse-koodi
                receivedData[i] = '\0'; // Poistetaan rivinvaihto
                System_printf("Received Morse: %s\n", receivedData);
                System_flush();

                // Käännetään morse-koodi tekstiksi
                morseToText(receivedData, outputText);
                System_printf("Decoded Message: %s\n", outputText);
                System_flush();

                // Nollataan vastaanotetut tiedot
                memset(receivedData, 0, MAX_MORSE_LEN);
                memset(outputText, 0, MAX_MORSE_LEN);
                i = 0;
            } else {
                // Lisätään vastaanotettu merkki
                i++;
            }
        }

        Task_sleep(100 / Clock_tickPeriod); // Taskin aikakatkaisu
    }
}
