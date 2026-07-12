/* Clear bit 1 of the hw60 high byte, set +0x1ae bit 0, then dispatch. */
extern int func_0203c634(int, int, void *);
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
extern int func_ov253_020cd760(int);
void func_ov253_020cd704(int param_1) {
    int owner = *(int *)(param_1 + 4);
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~2;
    *(unsigned short *)(*(int *)owner + 0x1ae) |= 1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020cd760);
}
