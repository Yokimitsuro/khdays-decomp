/* func_ov106_020b85a0 -- per-frame tick of the ov023 sub-scene: run the active slot's handler,
 * where the active index is the global at data_0204be04 and the slots are 4 bytes apart at +0x60
 * of the context. Always reports 0. */
extern void func_ov106_020b8990(int obj);
extern unsigned char data_0204be04;
extern int data_ov106_020b8b68;

int func_ov106_020b85a0(void) {
    int obj = *(int *)(*(int *)&data_ov106_020b8b68 + data_0204be04 * 4 + 0x60);
    if (obj != 0) {
        func_ov106_020b8990(obj);
    }
    return 0;
}
