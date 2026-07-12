/* Unless bit 0 of the hw60 low byte is set, mark state 2 and dispatch via c634. */
extern int func_0203c634(int, int, int);
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov253_020d2a74(int param_1) {
    int obj = *(int *)(*(int *)(param_1 + 4));
    if ((((struct hw60 *)(obj + 0x60))->lo & 1) == 0) return;
    *(signed char *)(obj + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
