/* Seeds the RNG/state block at data_0204c168: the two caller-supplied words at +0xc/+0x10
 * and the fixed LCG constants (0x6c078965 multiplier, 0x5d588b65 / 0x269ec3 pair) at
 * +0x14..+0x1c, then the live copy at +0..+8 with the counter at +0x20 cleared. */
extern int data_0204c168[];

void func_02023e34(int a, int b, int c) {
    data_0204c168[3] = b;
    data_0204c168[4] = c;
    data_0204c168[5] = 0x6c078965;
    data_0204c168[6] = 0x5d588b65;
    data_0204c168[7] = 0x269ec3;
    data_0204c168[8] = 0;
    data_0204c168[0] = a;
    data_0204c168[1] = 0x5d588b65;
    data_0204c168[2] = 0x269ec3;
}
