/* NONMATCHING: addressing tie. The slot value *(arg0+i*4+0x2b98) is read twice
 * (guard + func_020236ac arg); mwcc materializes the 0x2b98 offset with two
 * different splits (0x2000+0xb98 vs 0x398+0x2800) using an extra reg. A local
 * cache shortens it (72B); the array-index form overshoots (r7). Structure/size
 * otherwise match (80B). Calls func_0202a440 + func_020236ac for each nonzero of
 * the 6 slots. */
extern void func_0202a440(int arg0);
extern void func_020236ac(int arg0);
void func_ov022_02097cd0(int arg0) {
    int e = arg0 + 0x2ac0, i = 0;
    do {
        if (((int *)arg0)[i + 0xae6] != 0) { func_0202a440(e); func_020236ac(((int *)arg0)[i + 0xae6]); }
        i++; e += 0x24;
    } while (i < 6);
}
