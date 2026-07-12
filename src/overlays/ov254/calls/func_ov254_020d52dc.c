/* Kick the animation selected by +0xc on the object, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov254_020d52ac(int);
void func_ov254_020d52dc(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, *(unsigned char *)(owner + 0xc), 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov254_020d52ac);
}
