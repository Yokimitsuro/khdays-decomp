/* Kick anim 7 and the +0x428 sub-anim 3, notify 020cd148, clear +0x70/+0x7b, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov260_020cd148(int, int, int);
extern int func_ov260_020cfe84(int);
void func_ov260_020cfe20(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 7, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x428), 3, 0);
    func_ov260_020cd148(*(int *)owner, 0x12, *(int *)(owner + 0x10));
    *(int *)(owner + 0x70) = 0;
    *(signed char *)(owner + 0x7b) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov260_020cfe84);
}
