/* func_ov025_0209e194 -- twin of func_ov025_0209e168 for the other DMA0 hook. */
extern int func_ov025_02084afc(void);
extern void OSi_IrqDma0_0x020afcbc(void);

struct Ov025Bits { int b01 : 2, b23 : 2, rest : 28; };

void func_ov025_0209e194(void) {
    int ctx = func_ov025_02084afc();
    if (((struct Ov025Bits *)(ctx + 0xc))->b01 != 0) {
        return;
    }
    if (((struct Ov025Bits *)(ctx + 0xc))->b23 != 0) {
        return;
    }
    OSi_IrqDma0_0x020afcbc();
}
