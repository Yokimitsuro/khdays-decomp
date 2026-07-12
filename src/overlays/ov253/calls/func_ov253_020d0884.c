/* Clear the +0x38c gate byte and set bit 0 of the +0x3b4 status byte, then dispatch. */
extern int func_0203c634(int, int, void *);
struct b8 { unsigned int f : 8; };
extern int func_ov253_020d08d8(int);
void func_ov253_020d0884(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(signed char *)(*(int *)(*(int *)owner + 0x38c) + 0xa8) = 0;
    ((struct b8 *)(*(int *)(*(int *)owner + 0x3b4) + 8))->f |= 1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020d08d8);
}
