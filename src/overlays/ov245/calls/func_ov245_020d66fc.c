/* Kick anim 4, clear +0x40/+0x48/+0x49, arm the 020c5af8 timer, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov245_020d6758(int);
void func_ov245_020d66fc(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 4, 0);
    *(int *)(owner + 0x40) = 0;
    *(signed char *)(owner + 0x48) = 0;
    *(signed char *)(owner + 0x49) = 0;
    func_ov107_020c5af8(*(int *)owner, 0x11a, 7, *(int *)(owner + 0xc));
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov245_020d6758);
}
