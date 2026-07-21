/* Wait out the recovery window (node+0xc += owner delta); once past 0x100, hide the two reaction
 * icons (slots 0 and 2, state 2) and register the think callback. */
extern void func_0203b9fc(int obj, int slot, int a, int b);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov235_020d22b0(void);

void func_ov235_020d224c(int *param_1) {
    int node = param_1[1];
    int cd;
    cd = *(int *)(node + 0xc) + *(int *)(*param_1 + 0x2c);
    *(int *)(node + 0xc) = cd;
    if (cd < 0x100) {
        return;
    }
    func_0203b9fc(*(int *)(node + 4), 0, 2, 0);
    func_0203b9fc(*(int *)(node + 4), 2, 2, 0);
    func_0203c634((int)param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov235_020d22b0);
}
