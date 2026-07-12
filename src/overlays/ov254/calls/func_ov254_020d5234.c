/* Unless the child is busy, kick anim (1, phase 1) and dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov254_020d51fc(int);
void func_ov254_020d5234(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)owner, 1, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov254_020d51fc);
}
