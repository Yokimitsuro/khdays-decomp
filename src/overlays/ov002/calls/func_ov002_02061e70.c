/* Set sub-node 4 of the context's widget at +0x610 to the full Q12 value when
 * enabling and to zero when disabling, then refresh it. Does nothing with no
 * context installed. */
extern void func_01fff774(void *node, int slot, int value);
extern void func_0202af1c(void *node);

extern char *data_ov002_0207f628;

void func_ov002_02061e70(int enable) {
    char *ctx = data_ov002_0207f628;

    if (ctx == 0) {
        return;
    }

    func_01fff774(ctx + 0x610, 4, enable != 0 ? 0x1000 : 0);
    func_0202af1c(ctx + 0x610);
}
