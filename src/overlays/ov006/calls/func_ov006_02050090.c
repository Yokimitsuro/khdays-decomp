/* func_ov006_02050090 -- test whether the Mission Mode may accept a confirm, ov006.
 * True only when the Mission Mode is idle (base+0x28 == 0) and the confirm-ready check
 * (func_ov006_0204f2f4) passes. */
extern int func_ov006_0204f2f4(void);
extern int data_ov006_02056660;

int func_ov006_02050090(void) {
    if (*(int *)(data_ov006_02056660 + 0x28) == 0 && func_ov006_0204f2f4() != 0) {
        return 1;
    }
    return 0;
}
