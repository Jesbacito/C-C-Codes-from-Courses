//käytetty apuna tekoälyä chatgpt
//ensimmäinen prompt tehtävänanto, seuraavana saatu virhekoodi:
// 1	kuusikulmio.c:5:9: error: no previous prototype for ‘kuusikulmio’ [-Werror=missing-prototypes]		
// 2	    5 | uint8_t kuusikulmio(uint32_t luku) {		
// 3	      |         ^~~~~~~~~~~		
// 4	cc1: some warnings being treated as errors
// korjauksina tehty funktion kuusikulmio määrittely riville 13

#include <stdio.h>
#include <math.h>
#include <inttypes.h>

uint8_t kuusikulmio(uint32_t luku);

uint8_t kuusikulmio(uint32_t luku) {
                                                // Lasketaan n kaavasta: n = (1 + sqrt(1 + 8 * luku)) / 4
    double discriminant = 1 + 8 * (double)luku; // sqrt = neliöjuuri operandi
    double n = (1 + sqrt(discriminant)) / 4;
    
    if (n == (uint32_t)n) {                     // tarkistus onko n kokonaisluku
        uint32_t H_n = 2 * (uint32_t)n * (uint32_t)n - (uint32_t)n;
        if (H_n == luku) {
            return 1;                           // funktio tarkistaa sopiiko kokonaisluku n funktioon ja tuleeko vastaukseksi 1
        }
    }
    
    return 0;
}

int main() {
    uint32_t testiluku = 45;  // 45 on kuusikulmioluku (H_5 = 45)
    if (kuusikulmio(testiluku)) {
        printf("%" PRIu32 " on kuusikulmioluku.\n", testiluku);
    } else {
        printf("%" PRIu32 " ei ole kuusikulmioluku.\n", testiluku);
    }

    return 0;
}
