/* Run 020cce08 and 020d4810, set bit 1 of the +0x3b4 status byte, then dispatch. */
extern int func_0203c634(int, int, void *);
struct b8 { unsigned int f : 8; };
extern int func_ov245_020cce08(int);
extern int func_ov245_020d4810(int);
extern int func_ov245_020ce3f4(int);
void func_ov245_020ce394(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov245_020cce08(*(int *)owner);
    func_ov245_020d4810(*(int *)(*(int *)owner + 0x438));
    ((struct b8 *)(*(int *)(*(int *)owner + 0x3b4) + 8))->f |= 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov245_020ce3f4);
}
