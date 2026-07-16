/* func_ov006_0204eca4 -- return the title update handler func_ov006_0204ece4 when the input
 * object is idle (ctx+0x4e8 == 0) and func_ov006_0204e5bc allows it, else 0. */
extern int  func_ov006_0204e5bc(void);
extern void func_ov006_0204ece4(void);
extern int  data_ov006_020565e4;   /* -> title-screen context */

int func_ov006_0204eca4(void) {
    if (*(int *)(data_ov006_020565e4 + 0x4e8) == 0 && func_ov006_0204e5bc() != 0) {
        return (int)func_ov006_0204ece4;
    }
    return 0;
}
