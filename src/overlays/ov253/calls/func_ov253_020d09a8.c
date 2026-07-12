/* Kick anim 4, set bit 0 of the +0x3b4 status byte, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
struct b8 { unsigned int f : 8; };
extern int func_ov253_020d0a04(int);
void func_ov253_020d09a8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 4, 0);
    ((struct b8 *)(*(int *)(*(int *)owner + 0x3b4) + 8))->f |= 1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020d0a04);
}
