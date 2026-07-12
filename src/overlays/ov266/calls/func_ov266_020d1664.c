/* If the linked partner (+0x5ac -> +0x18c) is present, cache it into +0xc and when non-null fire
 * its 0x15e/0xd effect and notify func_ov266_020cf3dc; always kick anim 8, clear +0x50 and dispatch. */
extern int func_ov022_020ad8e0(int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_ov266_020cf3dc(int, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov266_020d16e8(int);
void func_ov266_020d1664(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int t = *(int *)(*(int *)owner + 0x5ac);
    if (t != 0) {
        int v = *(int *)(t + 0x18c);
        *(int *)(owner + 0xc) = v;
        if (v != 0) {
            func_ov022_020ad8e0(v, 1);
            func_ov107_020c5af8(*(int *)owner, 0x15e, 0xd, *(int *)(owner + 8));
            func_ov266_020cf3dc(owner, 1);
        }
    }
    func_ov107_020c9264(*(int *)owner, 8, 0);
    *(int *)(owner + 0x50) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov266_020d16e8);
}
