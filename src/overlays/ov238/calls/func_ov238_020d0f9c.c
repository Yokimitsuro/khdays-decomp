/* Clear bit 0 of the +8 status byte of *(obj+0x38c), then dispatch via c634. */
extern int func_0203c634(int, int, void *);
struct b8 { unsigned int f : 8; };
extern int func_ov238_020d0fe0(int);
void func_ov238_020d0f9c(int param_1) {
    int p = *(int *)(*(int *)(*(int *)(param_1 + 4)) + 0x38c);
    ((struct b8 *)(p + 8))->f &= ~1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov238_020d0fe0);
}
