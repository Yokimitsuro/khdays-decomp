/* func_ov023_02089848 -- per-frame tick of the ov023 sub-scene: run the active slot's handler,
 * where the active index is the global at data_0204be04 and the slots are 4 bytes apart at +0x60
 * of the context. Always reports 0. */
extern void func_ov023_02089c38(int obj);
extern unsigned char data_0204be04;
extern int data_ov023_0208a7c0;

int func_ov023_02089848(void) {
    int obj = *(int *)(*(int *)&data_ov023_0208a7c0 + data_0204be04 * 4 + 0x60);
    if (obj != 0) {
        func_ov023_02089c38(obj);
    }
    return 0;
}
