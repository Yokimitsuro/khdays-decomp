/* Clear bits 0-1 of the +0x444 status byte and set the +0x1ae bits, then dispatch. */
extern int func_0203c634(int, int, void *);
struct b8 { unsigned int f : 8; };
void func_ov253_020ce3a4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    ((struct b8 *)(*(int *)(*(int *)owner + 0x444) + 8))->f &= ~3;
    *(unsigned short *)(*(int *)owner + 0x1ae) |= 3;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
