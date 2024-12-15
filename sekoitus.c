//käytetty apuna tekoälyä chatgpt, ensimmäinen prompt tehtävänanto
//itse lisäillyt selityksiä riveille sekä funktion shufflen määrittely

//korjauksia varten annettu promptina väärän tuloksen virhekoodi sekä oikea tulos

//pyydetty tekemään funkti9o niin, että käänteisen järjestyksen sijaan alkuperäinen
//taulukko käydään läpi sen alkuperäisessä järjestyksessä
//korjaus shuffle-funktioon 

//promptina: tarkistin kaatuu
//korjauksia: taulukon minimikoon tarkistus, tehty tarkennus indeksin valintaan

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

void shuffle(uint8_t *list, uint16_t list_size);    //uint8_t *list osoittaa taulukkoon jota sekoitetaan

void shuffle(uint8_t *list, uint16_t list_size) {  
    if (list_size < 2) return;                      //Varmistus, että taulukossa on väh. 2 alkiota, jotta sekoitus voidaan tehdä
    
    for (int i = list_size - 1; i > 0; i--) {       //loop generoi satunnaisen indeksin taulukosta
        uint16_t j = rand() % (i + 1);              //indeksi valitaan vain jo olemassa olevien joukosta jotta vältetään 
                                                    //muistin ylivuoto
        uint8_t temp = list[i];                     //vaihdetaan alkioiden list[i] ja list[j] paikkoja jotta niiden
        list[i] = list[j];                          //paikat varmasti vaihtuvat
        list[j] = temp;
    }
}

int main() {
    srand(time(NULL));                              //satunnaisten lukujen tuomista varten generaattori

    uint8_t list[7] = { 1, 2, 3, 4, 5, 6, 7 };

    printf("Before shuffle: ");                     //taulukon sisältö ennen sekoitusta
    for (int i = 0; i < 7; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    shuffle(list, 7);                               //sekoitus operandi

    printf("After shuffle:  ");                     //taulukon sisältö, kun sekoitus on valmis
    for (int i = 0; i < 7; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    return 0;
}
