/* func_ov006_0204ece4 -- if the shared flag is set run func_02030610, advance title input
 * (func_ov006_0204dbb4), then return the idle handler func_ov006_0204ed24 when ctx+0x49c is
 * clear, else 0. */
extern int  func_02030640(void);   /* shared-flag test */
extern void func_02030610(void);
extern void func_ov006_0204dbb4(void);
extern void func_ov006_0204ed24(void);
extern int  data_ov006_020565e4;   /* -> title-screen context */

int func_ov006_0204ece4(void) {
    int result = 0;
    if (func_02030640() != 0) {
        func_02030610();
    }
    func_ov006_0204dbb4();
    if (*(int *)(data_ov006_020565e4 + 0x49c) == 0) {
        result = (int)func_ov006_0204ed24;
    }
    return result;
}
