/* Main state of the ov106 scene. On the sub screen (+0x8e48 = 1), once the caption script finishes
 * (02020e58) it is closed and, for end kinds 0-2 (+0x12c; kind 1 also starts +0x130), the layers are
 * reset and the state moves on to 020b7728. Otherwise the layers are refreshed, the main screen runs
 * its camera step, the frame is committed (02023c30) and a set field 0x20e6 starts the exit (020b8130);
 * the state stays. */
extern char *data_ov106_020b8b60;
extern int func_02020e58(void *script);
extern void func_02020cc8(void *script);
extern void func_ov002_0206ba28(int a);
extern void func_ov106_020b7c50(void);
extern void func_ov106_020b7f08(void);
extern void func_02023c30(int a);
extern unsigned int func_020235d0(int nField, int nBits);
extern void func_ov106_020b8130(void);
extern int func_ov106_020b7728(void);

void *func_ov106_020b7918(void)
{
    if (*(int *)(data_ov106_020b8b60 + 0x8e48) == 1 && func_02020e58(data_ov106_020b8b60) == 0) {
        func_02020cc8(data_ov106_020b8b60);
        switch (*(int *)(data_ov106_020b8b60 + 0x12c)) {
        case 1:
            func_ov002_0206ba28(*(int *)(data_ov106_020b8b60 + 0x130));
        case 0:
        case 2:
            func_ov106_020b7c50();
            return func_ov106_020b7728;
        }
    }
    func_ov106_020b7c50();
    if (*(int *)(data_ov106_020b8b60 + 0x8e48) == 0) {
        func_ov106_020b7f08();
    }
    func_02023c30(2);
    if (func_020235d0(0x20e6, 1) == 1) {
        func_ov106_020b8130();
    }
    return 0;
}
