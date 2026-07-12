/* Count the +0x1c timer up; past 0x2000 kick anim 3 and dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov253_020d3164(int);
void func_ov253_020d3118(int param_1) {
    int a = *(int *)param_1;
    int owner = *(int *)(param_1 + 4);
    int t = *(int *)(owner + 0x1c) + *(int *)(a + 0x2c);
    *(int *)(owner + 0x1c) = t;
    if (t < 0x2000) return;
    func_ov107_020c9264(*(int *)owner, 3, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020d3164);
}
