/* Confirm the current selection, but only while bit 2 of the state word at
 * +0x110 is set: close the sub-panel, relayout, play the sound the context
 * carries at +0x198 and park the panel state at +0x18c on 2. */
extern void func_ov002_020557f4(int a);
extern void func_ov002_02055490(void);
extern void func_02033b24(int a, int sound);

extern char *data_ov002_0207f614;

void func_ov002_02055bd0(void) {
    char *ctx = data_ov002_0207f614;

    if (((unsigned int)(*(int *)(ctx + 0x110) << 0x1d) >> 0x1f) == 0) {
        return;
    }

    func_ov002_020557f4(1);
    func_ov002_02055490();
    func_02033b24(0, *(int *)(ctx + 0x198));
    *(int *)(ctx + 0x18c) = 2;
}
