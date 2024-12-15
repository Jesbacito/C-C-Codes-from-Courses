// Jessika

#ifndef MORSE_CONTROL_H
#define MORSE_CONTROL_H

#include <stdint.h>
#include <ti/drivers/UART.h>

// Makrot
#define MORSE_UNIT 1000 // 1 sekunti (1 yksikkö) on 1000 ms
#define MAX_MORSE_LEN 256
#define MOVE_LEFT_RIGHT_THRESHOLD 2000 // Oikealle liikkeen kesto (2s)
#define MOVE_RETURN_THRESHOLD 1000     // Palautusliikkeen kesto (1s)
#define MOVE_LIFT_LOWER_THRESHOLD 1000 // Nosto-lasku kesto (1s)

// Globaalit muuttujat
extern char morseCode[MAX_MORSE_LEN];
extern int morseIndex;
extern UART_Handle uart;

// Morse-taulukko
extern const char *morseTable[];

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

// Funktiot
const char* charToMorse(char ch);
void textToMorse(const char* text, char* morseCode);
void sendMorseCode(char *morse);
uint32_t getMotionData();
uint32_t getMoveDuration();
void sensorTaskFxn(UArg arg0, UArg arg1);

#endif // MORSE_CONTROL_H
