extern int GX_SetBankForTex(int);
extern int func_02010f08(void);
extern int func_02010e80(int a, int b);
extern int GXS_SetGraphicsMode(int);
extern void MIi_CpuClearFast(int value, void *dst, int size);
extern int SNDi_UnlockMutex_0x020065d4(void);
extern int func_0202e844(void);
extern int func_02023c30(int a);

extern char data_0204c214[];

/* Reset the display: reassign the texture bank, select graphics mode 3, and wipe
 * ALL of VRAM through the LCDC window (0x06800000, 0xa4000 = banks A-I linear),
 * then seed the caller's state block.  Sibling of func_0202e944, which brings up
 * the sub engine and sets the same data_0204c214 ready flag.
 *
 * The `return 1` is load-bearing, not cosmetic: r0 is reserved for it, so the 1
 * being stored into data_0204c214 lives in r0 and the pool address is forced into
 * r1.  Written as void, mwcc hoists the pool load into the load-delay slot ahead
 * of the `self[0]` store and swaps the pair. */
int func_0202e8ec(int *self, int arg) {
    GX_SetBankForTex(3);
    func_02010f08();
    func_02010e80(2, 1);
    GXS_SetGraphicsMode(3);
    MIi_CpuClearFast(0, (void *)0x06800000, 0xa4000);
    SNDi_UnlockMutex_0x020065d4();
    func_0202e844();
    func_02023c30(2);
    self[1] = 1;
    self[2] = 1;
    self[3] = 0x10;
    self[0] = (arg != 0);
    *data_0204c214 = 1;
    return 1;
}
