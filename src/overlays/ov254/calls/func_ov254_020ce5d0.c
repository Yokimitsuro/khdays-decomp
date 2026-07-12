/* Kick anim (0 if +0x78 set else 0xb), then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov254_020ce610(int);
void func_ov254_020ce5d0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, *(int *)(owner + 0x78) != 0 ? 0 : 0xb, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov254_020ce610);
}
