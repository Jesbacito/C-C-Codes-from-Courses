//Jessika: morse-koodin kääntö länsimaisiksi aakkosiksi. Morse-kirjaimet hakutaulukkona. Includet vielä mukana

#include <stdio.h>
#include <string.h>

typedef struct {
    char letter;
    const char *morse;
} MorseCode;

MorseCode morseTable[] = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
    {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."},
    {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
    {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."},
    {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
    {'Y', "-.--"}, {'Z', "--.."}
};

char translateMorseToLetter(const char *morse) {
    for (int i = 0; i < sizeof(morseTable) / sizeof(morseTable[0]); i++) {
        if (strcmp(morseTable[i].morse, morse) == 0) {
            return morseTable[i].letter;
        }
    }
    return '?'; // Virhetilanne: jos morse-koodi ei vastaa mitään kirjainta
}

int printLetter() {
    // Oletan tässä, että inputMorse tulee sensortagin datasta
    const char *inputMorse = "...";
    
    char result = translateMorseToLetter(inputMorse);
    
    if (result != '?') {
        printf(%c\n, result);
    } else {
        printf("Tuntematon morse-koodi: %s\n", inputMorse);
    }
    
    return 0;
}