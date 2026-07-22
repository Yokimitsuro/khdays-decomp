/* Returns the address of entry `i` of record `a` (the halfword array at +0xba, stride 4)
 * when the index is inside func_0203595c(a)'s count and the corresponding count halfword
 * -- reached through the separate symbol data_0204c732, which is data_0204c678 + 0xba --
 * is non-zero.  NULL otherwise. */
extern int func_0203595c(int a);
extern unsigned char data_0204c732[];
extern unsigned char data_0204c678[];

unsigned short *func_02035978(int a, int i) {
    unsigned short *r = 0;
    int n = func_0203595c(a);
    if (i >= 0 && i < n &&
        *(unsigned short *)(data_0204c732 + a * 260 + i * 4) != 0) {
        r = (unsigned short *)(data_0204c678 + a * 260 + 0xba + i * 4);
    }
    return r;
}
