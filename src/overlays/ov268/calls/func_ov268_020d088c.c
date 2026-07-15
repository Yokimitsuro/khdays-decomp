/* For each un-flagged (0x2000) entity in param_1's list (count at param_1+2), stage its
 * pos (e+0x84/+0x88) into a 2-word buffer and call func_ov268_020d096c with the entity's
 * shape params, the source rect (param_2), the 4 precomputed rect corners, and an in/out
 * hit accumulator; stop early once the accumulator reaches 4. Returns the accumulator. */
extern int func_ov268_020d096c(int *buf, int a, int b, int c, int *rect, int *corners,
                               int *acc, int arg);
int func_ov268_020d088c(int param_1, int *param_2, int param_3, int param_4) {
    struct { int buf[2]; int acc; int corners[4]; } f;
    int i;
    f.acc = 0;
    f.corners[0] = param_2[0] - param_2[3];
    f.corners[1] = param_2[2] - param_2[3];
    f.corners[2] = param_2[0] + param_2[3];
    f.corners[3] = param_2[2] + param_2[3];
    for (i = 0; i < *(unsigned short *)(param_1 + 2); i++) {
        int e = (*(int **)(param_1 + 4))[i];
        if ((*(unsigned short *)(e + 0x74) & 0x2000) == 0) {
            f.buf[0] = *(int *)(e + 0x84);
            f.buf[1] = *(int *)(e + 0x88);
            func_ov268_020d096c(f.buf, *(int *)(e + 0x8c), *(int *)(e + 0x9c),
                                *(int *)(e + 0xa4), param_2, f.corners, &f.acc, param_3);
            if (f.acc >= 4) {
                break;
            }
        }
    }
    return f.acc;
}
