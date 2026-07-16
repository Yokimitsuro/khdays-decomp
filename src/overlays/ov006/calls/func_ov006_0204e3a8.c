/* func_ov006_0204e3a8 -- fire the Mission Mode-screen exit message 0x200d (dispatch when the input
 * object at ctx+0x4e8 is idle, else forward), run teardown func_ov006_0204dc04, and drop the
 * context pointer. */
extern void func_020235bc(int msg);
extern void func_020235a8(int msg);
extern void func_ov006_0204dc04(void);
extern int  data_ov006_020565e4;   /* -> Mission Mode-screen context */

void func_ov006_0204e3a8(void) {
    if (*(int *)(data_ov006_020565e4 + 0x4e8) != 0) {
        func_020235a8(0x200d);
    } else {
        func_020235bc(0x200d);
    }
    func_ov006_0204dc04();
    data_ov006_020565e4 = 0;
}
