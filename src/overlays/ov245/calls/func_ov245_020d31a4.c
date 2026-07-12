/* Clear bit 0x80 in the high byte of the u16 flags at *(obj)+0x60 and register the handler. */
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov245_020d31ec(int);
void func_ov245_020d31a4(int param_1) {
    int obj = *(int *)*(int *)(param_1 + 4);
    ((struct hw60 *)(obj + 0x60))->hi &= ~0x80;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov245_020d31ec);
}
