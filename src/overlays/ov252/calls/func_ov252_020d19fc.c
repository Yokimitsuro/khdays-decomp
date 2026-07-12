/* Reset via 020cdfe8, store speed/3 into +0x7c; if armed (+0xac) and not already in sub-state 0xb,
 * set +0x88=8 and kick anims 0x32/0x36; always kick anim 1, restart 020c9ee8, clear +0x64, dispatch. */
extern int func_ov252_020cdfe8(int, int, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov252_020d1abc(int);
void func_ov252_020d19fc(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov252_020cdfe8(param_1, 0, 1);
    *(int *)(owner + 0x7c) = *(int *)(*(int *)param_1 + 0x2c) / 3;
    if (*(int *)(owner + 0xac) != 0) {
        if (*(signed char *)(*(int *)owner + 0x1c8) != 0xb) {
            *(unsigned char *)(owner + 0x88) = 8;
            func_ov107_020c9264(*(int *)owner, 0x32, 0);
            func_ov107_020c9264(*(int *)owner, 0x36, 0);
        }
    }
    func_ov107_020c9264(*(int *)owner, 1, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x574), 0, 0);
    *(int *)(owner + 0x64) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov252_020d1abc);
}
