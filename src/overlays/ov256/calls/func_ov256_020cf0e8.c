/* Play SFX 0x20b7, reset the linked node (+0x454=0), flag +0x80, clear +0x4c/+0x6a, kick anim
 * 0x12 and restart sub-anim 020c9ee8, then dispatch 020cf15c. */
extern int func_020235e8(int, int, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov256_020cf15c(int);
void func_ov256_020cf0e8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_020235e8(0x20b7, 8, 1);
    *(int *)(*(int *)owner + 0x454) = 0;
    *(int *)(owner + 0x80) = 1;
    *(int *)(owner + 0x4c) = 0;
    *(unsigned char *)(owner + 0x6a) = 0;
    func_ov107_020c9264(*(int *)owner, 0x12, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x450), 4, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020cf15c);
}
