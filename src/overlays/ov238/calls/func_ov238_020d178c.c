/* Kick anim 3, set +0x31=3 and clear +0x20, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov238_020d17d0(int);
void func_ov238_020d178c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 3, 0);
    *(signed char *)(owner + 0x31) = 3;
    *(int *)(owner + 0x20) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov238_020d17d0);
}
