/* srand: stores the PRNG seed into data_02046468. */

extern int data_02046468;

void srand_0x0200e090(int seed) {
    data_02046468 = seed;
}
