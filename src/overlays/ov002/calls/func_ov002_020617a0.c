/* Refresh the three sub-panels that are in a settled state (0 or 1): the pair at
 * +0xe8 and +0x8cc share one gate at +0xd58, and the one at +0xdc0 has its own
 * at +0xfec. Does nothing with no context installed. */
extern void func_ov002_02061784(void *panel);

extern char *data_ov002_0207f628;

void func_ov002_020617a0(void) {
    char *ctx = data_ov002_0207f628;

    if (ctx == 0) {
        return;
    }

    switch (*(int *)(ctx + 0xd58)) {
    case 0:
    case 1:
        func_ov002_02061784(ctx + 0xe8);
        func_ov002_02061784(ctx + 0x8cc);
        break;
    }

    switch (*(int *)(ctx + 0xfec)) {
    case 0:
    case 1:
        func_ov002_02061784(ctx + 0xdc0);
        break;
    }
}
