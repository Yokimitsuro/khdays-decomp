/* Claims the lowest free bit of the 8-bit allocation word at data_0204a2fc+4 and returns
 * its index, or -1 when all eight are taken. */
extern int data_0204a2fc[];

int func_02019d4c(void) {
    int mask = 1;
    int bits = data_0204a2fc[1];
    int i = 0;
    do {
        if ((bits & mask) == 0) {
            data_0204a2fc[1] |= mask;
            return i;
        }
        i = i + 1;
        mask = mask << 1;
    } while (i < 8);
    return -1;
}
