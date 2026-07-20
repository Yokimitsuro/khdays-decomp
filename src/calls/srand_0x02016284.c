/* srand: stores the PRNG seed into data_027e007c. */

extern int data_027e007c;

void srand_0x02016284(int seed) {
    data_027e007c = seed;
}
