/* Latch the queued sub-state +0x1c7 into +0x1c6, clear bit1 of the hw60 hi byte, dispatch the
 * matching handler, then reset +0x1c7 to -1. */
extern int func_0203c634(int, int, void *);
extern int func_ov245_020d3f84(int);
extern int func_ov245_020d403c(int);
extern int func_ov245_020d465c(int);
struct hw60 { unsigned short lo : 8, hi : 8; };
void func_ov245_020d3e74(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int sub = *(signed char *)(*(int *)owner + 0x1c7);
    if (sub != -1) {
        *(signed char *)(*(int *)owner + 0x1c6) = sub;
        ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~2;
        switch (*(signed char *)(*(int *)owner + 0x1c6)) {
        case 0: func_0203c634(param_1, 1, (void *)&func_ov245_020d3f84); break;
        case 1: func_0203c634(param_1, 1, (void *)&func_ov245_020d403c); break;
        case 2: func_0203c634(param_1, 1, (void *)&func_ov245_020d465c); break;
        }
    }
    *(signed char *)(*(int *)owner + 0x1c7) = -1;
}
