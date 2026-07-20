/* Tears down the active HUD node: unlink it, blank an engine-B BG register, and free its buffers.
 *
 * The node pointer lives at data_ov002_0207f638. Ov002_RemoveAndFreeNode releases the child at
 * +0x34; the engine-B BG register at 0x0400101c is zeroed before the frees; the optional buffers
 * at +0x14/+0x1c/+0x2c are freed if present; finally the node global is nulled.
 */

extern int *data_ov002_0207f638;
extern void func_ov002_02053904(int node);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void func_ov002_020655f8(void) {
    int node = (int)data_ov002_0207f638;

    func_ov002_02053904(*(int *)(node + 0x34));
    *(volatile int *)0x0400101c = 0;
    if (*(void **)(node + 0x14) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(node + 0x14));
    }
    if (*(void **)(node + 0x1c) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(node + 0x1c));
    }
    if (*(void **)(node + 0x2c) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(node + 0x2c));
    }
    data_ov002_0207f638 = 0;
}
