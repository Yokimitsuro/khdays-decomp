/* func_ov008_0208174c -- start a horizontal wipe to a new Mission Mode sub-state, ov006.
 * If the Mission Mode object exists, kicks a scroll animation on the Mission Mode layer (base+0x9544) from
 * x=-0x10000 to 0 over 600 units, commits it (func_02035ffc), and latches the pending sub-state
 * id (base+0x94f4 = arg). Returns 1 when started, 0 if there is no Mission Mode object. */
extern void func_02035fb0(unsigned int *anim, int a, int from, int to, int dur);
extern void func_02035ffc(int anim);
extern int  data_ov008_02090fa4;

int func_ov008_0208174c(int state) {
    if (data_ov008_02090fa4 != 0) {
        func_02035fb0((unsigned int *)(data_ov008_02090fa4 + 0x9544), 0, -0x10000, 0, 600);
        func_02035ffc(data_ov008_02090fa4 + 0x9544);
        *(int *)(data_ov008_02090fa4 + 0x94f4) = state;
        return 1;
    }
    return 0;
}
