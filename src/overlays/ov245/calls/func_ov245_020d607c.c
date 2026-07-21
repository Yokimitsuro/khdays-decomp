/* Transition to the block pose: set the hw60 high-byte bits 0x86 (blocking + facing-locked) and
 * clear the owner's "can be hit" low-byte flag (*node+0x388, +8 bit 0), then re-register the think
 * callback. */
struct LowByteFlags { unsigned bits : 8; };
extern void func_0203c634(int self, int idx, int cb);

void func_ov245_020d607c(int param_1) {
    int *node = *(int **)(param_1 + 4);
    unsigned short hw60;
    hw60 = *(unsigned short *)(*node + 0x60);
    *(unsigned short *)(*node + 0x60) =
        (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10);
    ((struct LowByteFlags *)(*(int *)(*node + 0x388) + 8))->bits &= ~1;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), 0);
}
