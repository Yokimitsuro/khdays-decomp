/* func_ov008_02051758 -- forward an input event to a pair of ov008 menu handler slots.
 * Looks up the current handler object in table A[index[0]] and calls its method at +0x28 with
 * param_1; if that returns 0 (unhandled) and param_2 is set, tries table B[index[1]]'s method
 * at +0x24 with param_2. One of a 12-member family differing only in the two method offsets. */
extern int func_ov008_020512e0(void *method, int arg);
extern int data_ov008_02090f0c[];   /* dispatch index[2] */
struct ov008_disp { char *obj; int _pad; };   /* 8-byte handler-table entry */
extern struct ov008_disp data_ov008_0209009c[];   /* handler table A */
extern struct ov008_disp data_ov008_02090064[];   /* handler table B */

int func_ov008_02051758(int param_1, int param_2) {
    int r = 0;
    void *m1 = *(void **)(data_ov008_0209009c[data_ov008_02090f0c[0]].obj + 0x28);
    if (param_1 != 0) {
        r = func_ov008_020512e0(m1, param_1);
    }
    if (r == 0) {
        void *m2 = *(void **)(data_ov008_02090064[data_ov008_02090f0c[1]].obj + 0x24);
        if (param_2 != 0) {
            r = func_ov008_020512e0(m2, param_2);
        }
    }
    return r;
}
