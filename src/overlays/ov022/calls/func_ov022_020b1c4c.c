extern int func_02033788(int a, int b);
extern int func_020339b0(int a, int b);

/* State 0 (and anything above 4) falls through the jump table to the shared
 * return, so it needs no case label. */
void func_ov022_020b1c4c(unsigned char *p) {
    switch (*p) {
    case 1:
    case 2:
        *p = 2;
        if (func_02033788(*(signed char *)(p + 6), *(short *)(p + 2))) *p = 3;
        return;
    case 3:
        if (*(short *)(p + 2) != *(short *)(p + 4) && *(short *)(p + 4) != -1) *p = 4;
        return;
    case 4:
        if (func_020339b0(*(signed char *)(p + 6), *(short *)(p + 2)) == 0) return;
        *p = 1;
        *(short *)(p + 2) = *(short *)(p + 4);
        *(short *)(p + 4) = -1;
        return;
    }
}
