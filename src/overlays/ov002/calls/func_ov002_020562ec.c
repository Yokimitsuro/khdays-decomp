/* Refresh the panel when bit 2 of the state word at +0x12c is set, then -- only
 * while func_ov002_02053840 agrees -- flush the display list at +0xbc if there
 * is a target at +0x4c. The state word at +0x18c is cleared either way once the
 * flush point is reached. */
extern void func_ov002_020554f0(void);
extern int func_ov002_02053840(void);
extern void func_020300f8(void *list);

extern char *data_ov002_0207f614;

void func_ov002_020562ec(void) {
    char *ctx = data_ov002_0207f614;

    if ((unsigned int)(*(int *)(ctx + 0x12c) << 0x1d) >> 0x1f) {
        func_ov002_020554f0();
    }

    if (func_ov002_02053840() == 0) {
        return;
    }

    if (*(int *)(ctx + 0x4c) != 0) {
        func_020300f8(ctx + 0xbc);
    }

    *(int *)(ctx + 0x18c) = 0;
}
