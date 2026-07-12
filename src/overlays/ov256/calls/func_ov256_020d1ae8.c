/* Clear bit 7 of the hw60 high byte, then dispatch via c634. */
extern int func_0203c634(int, int, void *);
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov256_020d1ae8(int param_1) {
    ((struct hw60 *)(*(int *)(*(int *)(param_1 + 4)) + 0x60))->hi &= ~0x80;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
