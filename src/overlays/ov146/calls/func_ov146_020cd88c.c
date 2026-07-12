/* Unless the sub-object is busy, kick anim 9 on it, set +0x58 and dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov146_020cd8d8(int);
void func_ov146_020cd88c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int obj = *(int *)(owner + 8);
    if (*(unsigned char *)(*(int *)(obj + 0x384) + 0xad) != 0) return;
    func_ov107_020c9264(obj, 9, 0);
    *(int *)(owner + 0x58) = 1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov146_020cd8d8);
}
