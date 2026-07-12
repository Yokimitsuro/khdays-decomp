/*
 * Read a palette/attribute byte selected by a mode nibble. From the global object,
 * the byte at +1 picks the index source (+5 when it is 9, else +2); the chosen
 * index addresses a byte at base + index*2 + 0x32.
 */
extern int data_ov002_0207f620;

unsigned int func_ov002_0205dc2c(void) {
    int base = *(int *)&data_ov002_0207f620;
    int idx;

    if (*(unsigned char *)(base + 1) == 9) {
        idx = *(unsigned char *)(base + 5);
    } else {
        idx = *(unsigned char *)(base + 2);
    }
    return *(unsigned char *)(base + idx * 2 + 0x32);
}
