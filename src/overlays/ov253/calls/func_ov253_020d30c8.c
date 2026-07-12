/* Count the +0x1c timer up; past 0x444 set +0x398=0x1000, reset it and dispatch. */
extern int func_0203c634(int, int, void *);
extern int func_ov253_020d3118(int);
void func_ov253_020d30c8(int param_1) {
    int a = *(int *)param_1;
    int owner = *(int *)(param_1 + 4);
    int t = *(int *)(owner + 0x1c) + *(int *)(a + 0x2c);
    *(int *)(owner + 0x1c) = t;
    if (t < 0x444) return;
    *(int *)(*(int *)owner + 0x398) = 0x1000;
    *(int *)(owner + 0x1c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020d3118);
}
