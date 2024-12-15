#include <stdio.h>
#include <stdint.h>

// Puuttuvat makrot ja vakioarvot
#define SET(reg, bit) ((reg) |= (1 << (bit)))
#define CLEAR(reg, bit) ((reg) &= ~(1 << (bit)))

// Vakioarvot
#define DATA_MASK 0x07F8  // 0b0000011111111000, kattaa bitit 10-3
#define RW_BIT 1          // RW-bitti on bitti 1 (0b0000 0000 0000 0010)
#define RESET_BIT 0       // RS-bitti on bitti 0 (0b0000 0000 0000 0001)

// Funktiot
void write_data_to_LCD(uint16_t* lcd_register, uint8_t data);
void reset_LCD(uint16_t* lcd_register);

// Kirjoita dataa LCD:lle
void write_data_to_LCD(uint16_t* lcd_register, uint8_t data) {
    // Tyhjennä aiemmat tiedot
    *lcd_register = *lcd_register & ~DATA_MASK; // 0b0000011111111000
    // Aseta uudet tiedot
    *lcd_register = *lcd_register | ((uint16_t)data << 3); 
    // Nollaa R/W-bitti merkiksi, että kyseessä on kirjoitustoiminto
    CLEAR(*lcd_register,RW_BIT);
}

// Nollaa LCD. Tämä asettaa Reset-bittiin arvon 1
void reset_LCD(uint16_t* lcd_register) {
    SET(*lcd_register,RESET_BIT);
}

// Kirjoita dataa LCD:lle ja nollaa se
int main() {
    uint16_t lcd_register = 0x00C8;
    write_data_to_LCD(&lcd_register, 0x19);
    printf("Kirjoitettu data LCD:lle. LCD-rekisterin sisältö: %#06X \n", lcd_register);
    reset_LCD(&lcd_register);
    printf("Nollataan rekisteri. LCD-rekisterin sisältö: %#06X \n", lcd_register);

    return 0;
}
