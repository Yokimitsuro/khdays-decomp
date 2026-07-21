extern char *data_ov002_0207fa00;
/* True when the pending id at rootCtx+0x8c94 has been assigned (not -1). */
int func_ov002_0206b864(void) {
    int ctx = (int)data_ov002_0207fa00 + 0x8000;
    if (*(int *)(ctx + 0xc94) != -1) {
        return 1;
    }
    return 0;
}
