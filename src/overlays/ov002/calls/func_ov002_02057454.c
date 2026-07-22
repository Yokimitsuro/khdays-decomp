/* Record the value for the given row at +0x1c4, then -- only once the transition
 * has finished, and only when the row is the one the empty/non-empty state at
 * +0x54 selects -- refresh the panel. */
extern int func_ov002_020573cc(void);
extern void func_ov002_020554f0(void);

extern char *data_ov002_0207f614;

void func_ov002_02057454(int row, int value) {
    *(int *)(data_ov002_0207f614 + row * 4 + 0x1c4) = value;

    if (func_ov002_020573cc() != 0) {
        return;
    }
    if (row != (*(int *)(data_ov002_0207f614 + 0x54) == 0)) {
        return;
    }
    func_ov002_020554f0();
}
