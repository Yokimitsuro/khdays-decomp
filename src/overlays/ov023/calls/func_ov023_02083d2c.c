/* func_ov023_02083d2c -- push a new value onto entry `idx` of the 0x14-byte tween table at +0x104
 * of the scene object. The current end value (+0x10) becomes the new start (+0), the caller's
 * target goes to +4, the duration to +0xc and the elapsed counter is cleared; a zero duration
 * means "apply immediately", so the end value is set as well. */
extern int data_ov023_0208a784;

void func_ov023_02083d2c(int idx, int a, int b) {
    int *base = (int *)(*(int *)((char *)&data_ov023_0208a784 + 4) + 0x104);
    int *slot = (int *)((char *)base + idx * 0x14);
    slot[0] = slot[4];
    slot[1] = a;
    slot[3] = b;
    slot[2] = 0;
    if (b == 0) {
        slot[4] = a;
    }
}
