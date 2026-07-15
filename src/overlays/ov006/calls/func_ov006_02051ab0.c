/* func_ov006_02051ab0 -- decide the title's input action from the pad + gate state, ov006.
 * Reduces the latched pad bits (data_0204c190) to a single selector: confirm (bit0) wins over
 * cancel (bit1). With confirm selected and the title fully active (base+0x20 != 0) and the
 * confirm repeat past 1 (func_ov006_0204fab8), requests action 1 (Start). With cancel selected,
 * requests action 3. Finally, when the title is not yet active (base+0x20 == 0) and the attract
 * timer expired (func_ov006_0204fb50 == 1), forces action 1. Returns the action code (0/1/3). */
extern int func_ov006_0204fab8(void);
extern int func_ov006_0204fb50(void);
extern unsigned short data_0204c190;
extern int data_ov006_02056660;

int func_ov006_02051ab0(void) {
    unsigned short flags = data_0204c190;
    int result = 0;
    int sel = 0;
    if (flags & 2) {
        sel = 2;
    }
    if (flags & 1) {
        sel = 1;
    }
    if ((sel & 1) && *(int *)(data_ov006_02056660 + 0x20) != 0 &&
        (unsigned int)func_ov006_0204fab8() > 1) {
        result = 1;
    }
    if (sel & 2) {
        result = 3;
    }
    if (*(int *)(data_ov006_02056660 + 0x20) == 0 && func_ov006_0204fb50() == 1) {
        result = 1;
    }
    return result;
}
