/* Re-read the clip/vector matrix for whichever of the two matrix slots (0x150 / 0x180) is enabled
 * and whose stored owner key (0x148 / 0x14c) matches this node's key: its 0xae byte when flag bit
 * 4 is set, else -1. */
typedef unsigned int u32;
typedef unsigned char u8;
extern void func_02016294(void *dst, void *src);

void func_ov025_0208c868(int node) {
    int ctx = *(int *)(*(int *)(node + 4) + 0x2c);
    u32 key;
    if (*(int *)(ctx + 0x140) != 0) {
        key = (*(u32 *)(node + 8) & 0x10) ? *(u8 *)(node + 0xae) : 0xffffffff;
        if (*(u32 *)(ctx + 0x148) == key) {
            func_02016294((void *)(ctx + 0x150), (void *)0);
        }
    }
    if (*(int *)(ctx + 0x144) == 0) {
        return;
    }
    key = (*(u32 *)(node + 8) & 0x10) ? *(u8 *)(node + 0xae) : 0xffffffff;
    if (*(u32 *)(ctx + 0x14c) != key) {
        return;
    }
    func_02016294((void *)(ctx + 0x180), (void *)0);
}
