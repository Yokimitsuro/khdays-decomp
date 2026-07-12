/* Clear the hw60 flag; unless busy mark state 2 and dispatch. */
extern int func_0203c634(int, int, void *);
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov245_020cff94(int param_1) {
    int owner = *(int *)(param_1 + 4);
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~0x80;
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
