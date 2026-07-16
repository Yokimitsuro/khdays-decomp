/* func_ov008_0207a210 -- fire the title-screen exit message 0x200d (dispatch when the input
 * object at ctx+0x4e8 is idle, else forward), run teardown func_ov008_02079a70, and drop the
 * context pointer. */
extern void func_020235bc(int msg);
extern void func_020235a8(int msg);
extern void func_ov008_02079a70(void);
extern int  data_ov008_02090f24;   /* -> title-screen context */

void func_ov008_0207a210(void) {
    if (*(int *)(data_ov008_02090f24 + 0x4e8) != 0) {
        func_020235a8(0x200d);
    } else {
        func_020235bc(0x200d);
    }
    func_ov008_02079a70();
    data_ov008_02090f24 = 0;
}
