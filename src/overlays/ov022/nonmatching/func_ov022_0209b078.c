/* NONMATCHING: register-coloring tie. The slot pointer e (r6) and the
 * sign-extended arg2 (r4) are colored swapped vs the original. Structure/size
 * identical (72B). Calls func_0202accc 5x over slot arg0+0x278c+arg1*0x108. */
extern void func_0202accc(int arg0, int arg1, int arg2, int arg3);
void func_ov022_0209b078(int arg0, int arg1, int arg2) {
    int e = arg0 + 0x278c + arg1 * 0x108;
    short a2 = arg2;
    unsigned int i = 0;
    do { func_0202accc(e, i & 0xffff, e + 0xe0, a2); i++; } while ((int)i < 5);
}
