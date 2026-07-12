/* Unless the sub-state at *(obj)+0x1c7 is already -1, copy it to +0x1c6, clear bits 0x9e in the
 * high byte of the u16 flags at *(obj)+0x60, dispatch a follow-up handler for sub-state 0 or 2,
 * and finally reset the sub-state to -1. */
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov273_020d47b0(int);
extern void func_ov273_020d4868(int);
void func_ov273_020d46ac(int param_1) {
    int child = *(int *)(param_1 + 4);
    signed char s = *(signed char *)(*(int *)child + 0x1c7);
    if (s == -1) return;
    *(signed char *)(*(int *)child + 0x1c6) = s;
    ((struct hw60 *)(*(int *)child + 0x60))->hi &= ~0x9e;
    switch (*(signed char *)(*(int *)child + 0x1c6)) {
    case 0: func_0203c634(param_1, 1, (void *)&func_ov273_020d47b0); break;
    case 2: func_0203c634(param_1, 1, (void *)&func_ov273_020d4868); break;
    }
    *(signed char *)(*(int *)child + 0x1c7) = -1;
}
