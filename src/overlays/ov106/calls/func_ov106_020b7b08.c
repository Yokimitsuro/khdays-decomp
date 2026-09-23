/* Per-frame task of the ov106 scene (skipped while 020208e0 is busy): the +0x8b38 camera mode (+0x8e4c)
 * is chosen (main screen: 0xf while ov002 053840 runs, else 1 at full fade or 0xd; sub screen: 1 while
 * the fade task runs, else 0), the interaction check runs, the camera applies the mode and reports
 * the active screen into +0x8e48 (mirrored to data_0204be04), the fades step and the sub engine's
 * layers follow the main screen. */
typedef unsigned char u8;

extern char *data_ov106_020b8b60;
extern u8 data_0204be04;
extern int func_020208e0(void);
extern int func_ov002_02053840(void);
extern int func_ov002_02053dc4(void);
extern int func_ov106_020b8a34(int param_1);
extern void func_ov106_020b7a3c(void);
extern void func_0202ea14(void *pCamera, int nMode);
extern char func_0202e9b8(void *request);
extern void func_ov106_020b7fa4(void);
extern void func_ov106_020b80a8(void);
extern void func_02034138(int arg0);

void func_ov106_020b7b08(void)
{
    if (func_020208e0() != 0) {
        return;
    }
    if (*(int *)(data_ov106_020b8b60 + 0x8e48) == 0) {
        if (func_ov002_02053840() == 0) {
            if (func_ov002_02053dc4() == 0x10) {
                *(int *)(data_ov106_020b8b60 + 0x8e4c) = 1;
            } else {
                *(int *)(data_ov106_020b8b60 + 0x8e4c) = 0xd;
            }
        } else {
            *(int *)(data_ov106_020b8b60 + 0x8e4c) = 0xf;
        }
    } else {
        if (func_ov106_020b8a34(1) == 0) {
            *(int *)(data_ov106_020b8b60 + 0x8e4c) = 0;
        } else {
            *(int *)(data_ov106_020b8b60 + 0x8e4c) = 1;
        }
    }
    func_ov106_020b7a3c();
    func_0202ea14(data_ov106_020b8b60 + 0x8b38, *(int *)(data_ov106_020b8b60 + 0x8e4c));
    *(int *)(data_ov106_020b8b60 + 0x8e48) = func_0202e9b8(data_ov106_020b8b60 + 0x8b38);
    data_0204be04 = *(int *)(data_ov106_020b8b60 + 0x8e48);
    func_ov106_020b7fa4();
    func_ov106_020b80a8();
    func_02034138(data_0204be04 == 0);
}
