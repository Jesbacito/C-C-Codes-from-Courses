//käytetty apuna chatgpt, annettu promptiksi tehtävänanto 
//itse lisätty funktion määrittely ja selityksiä

#include <stdint.h>

int8_t tictactoe_check(int8_t *gameboard, int win_len);

int8_t tictactoe_check(int8_t *gameboard, int win_len) {
    int player1_win = 0;  // Risti
    int player2_win = 0;  // Nolla
    
    // Tarkistetaan kaikki rivit (vaakasuorat)
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col <= 10 - win_len; col++) {
            int count1 = 0;
            int count2 = 0;

            for (int k = 0; k < win_len; k++) {
                if (gameboard[row * 10 + col + k] == 1) {
                    count1++;
                } else if (gameboard[row * 10 + col + k] == 2) {
                    count2++;
                }
            }
            if (count1 == win_len) player1_win++;
            if (count2 == win_len) player2_win++;
        }
    }

    // Tarkistetaan kaikki sarakkeet (pystysuorat)
    for (int col = 0; col < 10; col++) {
        for (int row = 0; row <= 10 - win_len; row++) {
            int count1 = 0;
            int count2 = 0;

            for (int k = 0; k < win_len; k++) {
                if (gameboard[(row + k) * 10 + col] == 1) {
                    count1++;
                } else if (gameboard[(row + k) * 10 + col] == 2) {
                    count2++;
                }
            }
            if (count1 == win_len) player1_win++;
            if (count2 == win_len) player2_win++;
        }
    }

    // Tarkistetaan diagonaalit
    for (int row = 0; row <= 10 - win_len; row++) {
        for (int col = 0; col <= 10 - win_len; col++) {
            int count1 = 0;
            int count2 = 0;

            for (int k = 0; k < win_len; k++) {
                if (gameboard[(row + k) * 10 + (col + k)] == 1) {
                    count1++;
                } else if (gameboard[(row + k) * 10 + (col + k)] == 2) {
                    count2++;
                }
            }
            if (count1 == win_len) player1_win++;
            if (count2 == win_len) player2_win++;
        }
    }

    // Tarkistetaan vastakkain diagonaalit
    for (int row = 0; row <= 10 - win_len; row++) {
        for (int col = win_len - 1; col < 10; col++) {
            int count1 = 0;
            int count2 = 0;

            for (int k = 0; k < win_len; k++) {
                if (gameboard[(row + k) * 10 + (col - k)] == 1) {
                    count1++;
                } else if (gameboard[(row + k) * 10 + (col - k)] == 2) {
                    count2++;
                }
            }
            if (count1 == win_len) player1_win++;
            if (count2 == win_len) player2_win++;
        }
    }

    // Tarkistetaan voittojen lukumäärä
    if (player1_win > 0 && player2_win > 0) {
        return 0; // Molemmat pelaajat voittavat
    }
    if (player1_win > 0) {
        return 1; // Risti voittaa
    }
    if (player2_win > 0) {
        return 2; // Nolla voittaa
    }

    return 0; // Ei voittajaa
}
