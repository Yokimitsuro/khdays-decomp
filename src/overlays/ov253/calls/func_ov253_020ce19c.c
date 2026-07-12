/* Advance the +0x1c timer; unless busy, tick +0x34: on 2 kick anim 8 and dispatch, else kick anim 0xb. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov253_020ce210(int);
void func_ov253_020ce19c(int param_1) {
    int a = *(int *)param_1;
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x1c) += *(int *)(a + 0x2c);
    if (*(unsigned char *)(*(int *)(owner + 4)) != 0) return;
    *(int *)(owner + 0x34) += 1;
    int obj = *(int *)owner;
    if (*(int *)(owner + 0x34) >= 2) {
        func_ov107_020c9264(obj, 8, 0);
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020ce210);
    } else {
        func_ov107_020c9264(obj, 0xb, 0);
    }
}
