/* func_ov006_0204fa88 -- Mission Mode: read the current key state and feed it to the Mission Mode input
 * handler. Uses the debug/replay key source (func_01fff974) when it is active
 * (func_02030640), otherwise the real hardware keys. */
extern int  func_02030640(void);
extern int  func_01fff974(void);
extern int  OS_IsTickAvailable_0x01ff8138(void);
extern int  func_ov006_0204feb0(short *keys);

int func_ov006_0204fa88(void) {
    short keys;
    if (func_02030640() != 0) {
        keys = (short)func_01fff974();
    } else {
        keys = (short)OS_IsTickAvailable_0x01ff8138();
    }
    return func_ov006_0204feb0(&keys);
}
