/* srand: stores the PRNG seed into data_027e0088. */

extern int data_027e0088;

void srand(int seed) {
    data_027e0088 = seed;
}
