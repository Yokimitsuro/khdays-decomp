/* Forward the pair to func_ov002_02063660, first publishing request kind 9 when
 * the caller asked for it AND the context's busy word at +0x1b8 is clear. */
extern void func_ov002_02057500(void);
extern void func_ov002_02063660(int a, int b);

extern char *data_ov002_0207f614;

void func_ov002_020574a4(int a, int b) {
    char *ctx = data_ov002_0207f614;

    if (*(int *)(ctx + 0x1b8) == 0 && b != 0) {
        func_ov002_02057500();
    }
    func_ov002_02063660(a, b);
}
