extern void G3X_Init(void);
extern void func_02015630(void);

/* After G3 init, set GXSTAT (0x04000600) bit 31 and clear bit 30 (matrix-stack
 * error/geometry-engine control), leaving the rest intact. */
void func_020163cc(void) {
    volatile unsigned int *reg_gxstat = (volatile unsigned int *)0x04000600;
    G3X_Init();
    func_02015630();
    *reg_gxstat = (*reg_gxstat & ~0xc0000000u) | 0x80000000u;
}
