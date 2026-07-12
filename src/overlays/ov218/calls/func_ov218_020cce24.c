/* Unless the hw60 gate bit is set, reset the timer and copy the queued state, then dispatch. */
extern int func_0203c634(int, int, void *);
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov218_020cce24(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if ((((struct hw60 *)(*(int *)owner + 0x60))->lo & 1) == 0) return;
    *(int *)(owner + 0x24) = 0;
    { int obj = *(int *)owner; *(signed char *)(obj + 0x1c7) = *(signed char *)(obj + 0x1c9); }
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
