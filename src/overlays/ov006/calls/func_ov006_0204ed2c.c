/* func_ov006_0204ed2c -- advance the Mission Mode input state (func_ov006_0204dbb4), then return the
 * "idle" handler func_ov006_0204ed5c if the busy field (ctx+0x49c) is clear, else 0. */
extern void func_ov006_0204dbb4(void);
extern void func_ov006_0204ed5c(void);
extern int  data_ov006_020565e4;   /* -> Mission Mode-screen context */

int func_ov006_0204ed2c(void) {
    int result = 0;
    func_ov006_0204dbb4();
    if (*(int *)(data_ov006_020565e4 + 0x49c) == 0) {
        result = (int)func_ov006_0204ed5c;
    }
    return result;
}
