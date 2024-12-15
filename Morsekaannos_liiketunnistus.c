//Jessika

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>
#include <ti/drivers/PIN.h>
#include <ti/drivers/UART.h>
#include <stdio.h>
#include <string.h>

#define MORSE_UNIT 1000 // 1 sekunti (1 yksikkö) on 1000 ms
#define MAX_MORSE_LEN 256

// Liiketunnistimen ohjaus
#define MOVE_LEFT_RIGHT_THRESHOLD 2000 // Oikealle liikkeen kesto (2s)
#define MOVE_RETURN_THRESHOLD 1000     // Palautusliikkeen kesto (1s)
#define MOVE_LIFT_LOWER_THRESHOLD 1000 // Nosto-lasku kesto (1s)

Char morseCode[MAX_MORSE_LEN];
int morseIndex = 0;

UART_Handle uart; // UART käsittelijä

// Morse-taulukko, jossa on merkit ja niiden vastaavat morse-koodit
const char *morseTable[] = {
    "A", ".-",  "B", "-...", "C", "-.-.", "D", "-..", "E", ".", "F", "..-.",
    "G", "--.", "H", "....", "I", "..", "J", ".---", "K", "-.-", "L", ".-..",
    "M", "--",  "N", "-.",  "O", "---", "P", ".--.", "Q", "--.-", "R", ".-.",
    "S", "...", "T", "-",   "U", "..-",  "V", "...-", "W", ".--", "X", "-..-",
    "Y", "-.--", "Z", "--..",
    "1", ".----", "2", "..---", "3", "...--", "4", "....-", "5", ".....",
    "6", "-....", "7", "--...", "8", "---..", "9", "----.", "0", "-----",
    ".", ".-.-.-", ",", "--..--", "?", "..--..", "!", "-.-.--", "(", "-.--.",
    ")", "-.--.-", " ", "/"
};

// Funktio, joka palauttaa morse-koodin annetulle merkille
const char* charToMorse(char ch) {
    for (int i = 0; i < sizeof(morseTable) / sizeof(morseTable[0]); i += 2) {
        if (ch == morseTable[i][0]) {
            return morseTable[i + 1];  // Palautetaan morse-koodi
        }
    }
    return NULL;  // Jos merkkiä ei löydy taulukosta, palautetaan NULL
}

// Funktio, joka kääntää normaalin tekstin morse-koodiksi
void textToMorse(const char* text, char* morseCode) {
    while (*text) {
        const char* morse = charToMorse(*text);
        if (morse != NULL) {
            strcat(morseCode, morse);   // Lisää morse-koodi koodiin
            strcat(morseCode, " ");     // Lisää välilyönti koodiin merkkien erottamiseksi
        }
        text++;
    }
}

void sendMorseCode(char *morse) {     // Lähetetään morse-koodi UARTin kautta
    UART_write(uart, morse, strlen(morse));
}

uint32_t getMotionData() {
    // Liiketunnistimen lukeminen, esimerkki SensorTagin kiihtyvyysdatasta
    int x, y, z;
    readAccelerometerData(&x, &y, &z);  // Oletetaan, että tämä funktio lukee kiihtyvyysarvot

     if (x > 2000) return MOVE_LEFT_RIGHT; // Oikealle liike
    else if (x < -2000) return MOVE_RETURN; // Palautusliike
    else if (y > 2000) return MOVE_LIFT_LOWER; // Nosto-lasku
    return 0; // Ei liikettä
}

uint32_t getMoveDuration() {
    static uint32_t startTime = 0;
    uint32_t currentTime = Clock_getTicks();

    if (startTime == 0) {
        startTime = currentTime; // Liikkeen aloitus
    }

    return currentTime - startTime; // Liikkeen kesto
}

Void sensorTaskFxn(UArg arg0, UArg arg1) {
    uint32_t motionData = 0; // Arvot, joita liiketunnistimelta luetaan
    uint32_t moveDuration = 0;
    char currentMorseSymbol[2];

    while (1) {
        motionData = getMotionData(); // Liiketunnistimen data toisesta luodusta funktiosta

        // Jos liike on havaitsemisrajalla
        if (motionData == MOVE_LEFT_RIGHT) {
            moveDuration = getMoveDuration(); // Hae liikkeen kesto (ms)

            if (moveDuration >= MOVE_LEFT_RIGHT_THRESHOLD) {     // Liike oikealle - viiva
                currentMorseSymbol[0] = '-';
                currentMorseSymbol[1] = '\0';
                strcat(morseCode, currentMorseSymbol);
            } else if (moveDuration >= MOVE_RETURN_THRESHOLD) {
                // Palautus - piste
                currentMorseSymbol[0] = '.';
                currentMorseSymbol[1] = '\0';
                strcat(morseCode, currentMorseSymbol);
            }
        } 
        else if (motionData == MOVE_LIFT_LOWER) {      // Nosto-lasku - välilyönti
            strcat(morseCode, " "); 
        }

        // 3 peräkkäistä välilyöntiä tarkoittaa viestin loppua
        if (morseCode[morseIndex - 1] == ' ' && morseCode[morseIndex - 2] == ' ' && morseCode[morseIndex - 3] == ' ') {  // Viestin loppu - lähetä morse-koodi
            sendMorseCode(morseCode);
            memset(morseCode, 0, MAX_MORSE_LEN); // Tyhjennetään koodi
            morseIndex = 0;
        }

        Task_sleep(500 / Clock_tickPeriod); // Tähän tarvitsee vielä asettaa sopiva aika task_sleepille
    }
}