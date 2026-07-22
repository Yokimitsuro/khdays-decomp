/* func_ov023_02082a44 -- ov023 first-frame gate: do nothing while bit 0 of the heap status
 * halfword is set; otherwise ask func_ov023_02083a48 whether the scene is ready and, if so, raise
 * bit 4. Always reports 0. The bit-0 test is SIGNED `> 0`, which is what the ROM's `movgt` shows. */
extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_ov023_02083a48(void);

int func_ov023_02082a44(void) {
    unsigned short *h = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    if ((*h & 1) > 0) {
        return 0;
    }
    if (func_ov023_02083a48() != 0) {
        *h |= 0x10;
    }
    return 0;
}
