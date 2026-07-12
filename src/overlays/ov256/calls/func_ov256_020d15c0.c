/* Reset the reaction slot (state -1, mark 1, clear hw60/1ae bits) then fan out three dispatches. */
extern int func_0203c634(int, int, void *);
struct hw60 { unsigned short lo : 8, hi : 8; };
extern int func_ov256_020d166c(int);
extern int func_ov256_020d1a40(int);
extern int func_ov256_020d1714(int);
void func_ov256_020d15c0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0xc) = *(int *)owner + 0xb0;
    *(signed char *)(*(int *)owner + 0x1c6) = 1;
    *(signed char *)(*(int *)owner + 0x1c7) = -1;
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~1;
    *(unsigned short *)(*(int *)owner + 0x1ae) &= ~1;
    func_0203c634(param_1, 0, (void *)&func_ov256_020d166c);
    func_0203c634(param_1, 1, (void *)&func_ov256_020d1a40);
    func_0203c634(param_1, 2, (void *)&func_ov256_020d1714);
}
