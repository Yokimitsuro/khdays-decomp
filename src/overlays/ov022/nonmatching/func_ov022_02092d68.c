/*
 * [nonmatching: register-coloring tie — 96B, structurally byte-identical]
 *
 * When node flag bit0 is set and byte@0x135 is nonzero, tears down the node's
 * sub-objects (func_020158b0/02015880/020279e0), copies a 36-byte template from
 * data_02047428, clears bits 0xa4 in the global at data_02047394+0xd4, and runs
 * func_0201574c.
 *
 * The ONLY divergence: the `*(u32*)(&data_02047394+0xd4) &= ~0xa4` RMW — the
 * original colors the pooled base address into r1 and the loaded value into r2
 * (`ldr r1,=data; ldr r2,[r1,#0xd4]; bic r2,#0xa4; str r2,[r1,#0xd4]`); mwcc
 * 3.0/139 picks the opposite (base r2, value r1). Identical scheduling and
 * instruction count — only the two physical registers swap. Neither the inline
 * `&=` form nor a split read/modify/write steers the base onto r1, so this is
 * left uncarved (byte-exact in the blob).
 */
extern void func_020158b0(unsigned int *arg0);
extern void MI_Copy36B(void *dst, void *src);
extern void func_02015880(unsigned int *arg0);
extern void func_0201574c(void);
extern void func_020279e0(unsigned int *arg0);
extern int data_02047428;
extern int data_02047394;

void func_ov022_02092d68(unsigned char *arg0) {
    if ((*arg0 & 1) != 0 && arg0[0x135] != 0) {
        func_020158b0((unsigned int *)(arg0 + 0xb4));
        MI_Copy36B((void *)(arg0 + 0x144), &data_02047428);
        *(unsigned int *)((char *)&data_02047394 + 0xd4) &= ~0xa4;
        func_02015880((unsigned int *)(arg0 + 0xa8));
        func_0201574c();
        func_020279e0((unsigned int *)(arg0 + 0x24));
    }
}
