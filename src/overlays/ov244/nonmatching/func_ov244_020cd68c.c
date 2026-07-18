/*
 * func_ov244_020cd68c -- x3 (ov244/...). Publish this entity's local transform to its render node.
 * Tick 020c6980(self), then block-copy the 11-word transform at self+0xa0 into the render node at
 * *(*(self+0x38c)) + 0x10.
 *
 * NON-MATCHING: the same inlined-block-copy scratch-register coloring tie as func_ov119_020cbfc4 (see
 * its note + deferred-ties.md). Size-exact, byte-exact except the two ldmia/stmia pointers: the ROM
 * colors the source pointer -> lr and dest -> ip (add lr,r4,#0xa0 / ldr ip,[..] / ldmia lr! / stmia
 * ip!); mwcc 3.0/139 colors source -> ip, dest -> lr. The choice is independent of source form (~8
 * variants tried on ov119). Result identical.
 */
struct blk11 { int w[11]; };
extern void func_ov107_020c6980(int self);

void func_ov244_020cd68c(int self) {
    func_ov107_020c6980(self);
    *(struct blk11 *)(*(int *)(*(int *)(self + 0x38c)) + 0x10) = *(struct blk11 *)(self + 0xa0);
}
