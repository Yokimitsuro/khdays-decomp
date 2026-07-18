/*
 * func_ov209_020d59f4 -- x3 (ov208/209/268). Release the two spawned sub-objects, unless locked.
 * If the mode byte *(s8)(self+0x1c6) != 1, release each live handle at self+0x39c and self+0x3a4
 * through 0203c650(*(self+0x3c), handle) and clear it. Always tick 020c7ca4(self).
 */
extern void func_0203c650(int scene, int handle);
extern void func_ov107_020c7ca4(int self);

void func_ov209_020d59f4(int self) {
    if (*(signed char *)(self + 0x1c6) != 1) {
        int handle = *(int *)(self + 0x39c);
        if (handle != 0) {
            func_0203c650(*(int *)(self + 0x3c), handle);
            *(int *)(self + 0x39c) = 0;
        }
        handle = *(int *)(self + 0x3a4);
        if (handle != 0) {
            func_0203c650(*(int *)(self + 0x3c), handle);
            *(int *)(self + 0x3a4) = 0;
        }
    }
    func_ov107_020c7ca4(self);
}
