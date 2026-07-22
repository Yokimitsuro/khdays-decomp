/* func_ov025_0209e168 -- run the DMA0 completion hook, but only while both 2-bit state fields of
 * the word at +0xc (bits 0..1 and bits 2..3) are zero. Both are SIGNED bitfields -- that is the
 * ROM's `lsl ; asrs` pair; unsigned fields would give `lsl ; lsrs`. */
extern int func_ov025_02084afc(void);
extern void OSi_IrqDma0_0x020afccc(void);

struct Ov025Bits { int b01 : 2, b23 : 2, rest : 28; };

void func_ov025_0209e168(void) {
    int ctx = func_ov025_02084afc();
    if (((struct Ov025Bits *)(ctx + 0xc))->b01 != 0) {
        return;
    }
    if (((struct Ov025Bits *)(ctx + 0xc))->b23 != 0) {
        return;
    }
    OSi_IrqDma0_0x020afccc();
}
