/* func_ov009_0204eba8 -- forward an input event to a pair of ov008 menu handler slots.
 * Looks up the current handler object in table A[index[0]] and calls its method at +0x30 with
 * param_1; if that returns 0 (unhandled) and param_2 is set, tries table B[index[1]]'s method
 * at +0x2c with param_2. One of a 12-member family differing only in the two method offsets. */
extern int func_ov009_0204e640(void *method, int arg);
extern int data_ov009_020563ec[];   /* dispatch index[2] */
struct ov008_disp { char *obj; int _pad; };   /* 8-byte handler-table entry */
extern struct ov008_disp data_ov009_020562dc[];   /* handler table A */
extern struct ov008_disp data_ov009_020562d4[];   /* handler table B */

int func_ov009_0204eba8(int param_1, int param_2) {
    int r = 0;
    void *m1 = *(void **)(data_ov009_020562dc[data_ov009_020563ec[0]].obj + 0x30);
    if (param_1 != 0) {
        r = func_ov009_0204e640(m1, param_1);
    }
    if (r == 0) {
        void *m2 = *(void **)(data_ov009_020562d4[data_ov009_020563ec[1]].obj + 0x2c);
        if (param_2 != 0) {
            r = func_ov009_0204e640(m2, param_2);
        }
    }
    return r;
}
