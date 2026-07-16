/* func_ov006_02055cfc -- start a title-screen fade/param tween on channel param_2 (0..3).
 * Interpolator lives at ctx+0x9684 + param_2*0x1c; runs from 0 to param_1<<12 (Q12) over param_3.
 * Returns 0 if the context is not up or the channel is out of range, else 1. */
extern void func_02035fb0(unsigned int *interp, int mode, unsigned int from, unsigned int to, unsigned int dur);
extern void func_02035ffc(unsigned int *interp);
extern int  data_ov006_02056664;   /* -> title-screen context */

int func_ov006_02055cfc(int param_1, unsigned int param_2, unsigned int param_3) {
    if (data_ov006_02056664 == 0) {
        return 0;
    }
    if (param_2 <= 3) {
        func_02035fb0((unsigned int *)(data_ov006_02056664 + 0x9684 + param_2 * 0x1c), 2, 0,
                      param_1 << 0xc, param_3);
        func_02035ffc((unsigned int *)(data_ov006_02056664 + 0x9684 + param_2 * 0x1c));
        return 1;
    }
    return 0;
}
