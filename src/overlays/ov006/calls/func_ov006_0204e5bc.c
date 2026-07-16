/* func_ov006_0204e5bc -- test whether the Mission Mode may advance past the intro, ov006.
 * Returns true immediately if the global gate func_020306b4 is engaged; otherwise returns
 * whether the Mission Mode's ready check func_ov006_0204f2f4 is non-zero. */
extern int func_020306b4(void);
extern int func_ov006_0204f2f4(void);

int func_ov006_0204e5bc(void) {
    if (func_020306b4() != 0) {
        return 1;
    }
    return func_ov006_0204f2f4() != 0;
}
