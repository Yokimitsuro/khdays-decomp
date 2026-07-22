/* Scene entry: the context IS the current root heap block. Re-bank the display
 * flags at +0x38 (clear 0x32000, set 0x1000), resolve the two objects the
 * archive at +0x44 provides into +0x7c and +0x84, seed +0xb4 with 0x1f and run
 * the setup. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov002_02050b90(int archive);
extern int func_ov002_02050b68(int archive);
extern void func_ov002_0204d0e0(void);

void func_ov002_0204d12c(void) {
    char *ctx = NNSi_FndGetCurrentRootHeap();

    *(int *)(ctx + 0x38) = *(int *)(ctx + 0x38) & ~0x32000 | 0x1000;
    *(int *)(ctx + 0x7c) = func_ov002_02050b90(*(int *)(ctx + 0x44));
    *(int *)(ctx + 0x84) = func_ov002_02050b68(*(int *)(ctx + 0x44));
    *(int *)(ctx + 0xb4) = 0x1f;
    func_ov002_0204d0e0();
}
