/* Unless busy or either sub-object still active, mark +0x6b and the queued state, then dispatch. */
extern int func_0203c634(int, int, void *);
void func_ov256_020cfb74(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    int obj = *(int *)owner;
    if (*(int *)(*(int *)(obj + 0x434) + 0x3a0) != 0 ||
        *(int *)(*(int *)(obj + 0x438) + 0x3a0) != 0) return;
    *(signed char *)(owner + 0x6b) = 2;
    *(signed char *)(*(int *)owner + 0x1c7) = *(int *)(owner + 0x74) + 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
