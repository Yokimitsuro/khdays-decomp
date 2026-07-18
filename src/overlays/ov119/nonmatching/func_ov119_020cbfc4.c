/*
 * func_ov119_020cbfc4 -- x3 (ov119/...). Refresh sub-node #0's local transform, then publish it.
 * Copy the 4-word const at data_020cc028 to a scratch, run 0202ef54(node+4, node+4, &scratch) in
 * place (node = *(self+0x390)), then block-copy the 11-word transform at node+4 into the shared
 * output block at *(*(self+0x3a8))+4.
 *
 * NON-MATCHING: size-exact (104B) and every instruction matches EXCEPT the two scratch registers of
 * the 11-word struct-copy block. The ROM colors the source pointer -> lr and the dest pointer -> ip
 * (add lr,r0,#4 / add r12,r1,#4 / ldmia lr! / stmia r12!); mwcc 3.0/139 always colors source -> ip
 * and dest -> lr. Tried: inline struct assignment, explicit src/dst pointer locals in both
 * declaration orders, reusing the `node` local for the source, splitting the dest deref into its own
 * statement, negative-offset aliasing -- every form emits source->ip. This is the struct-copy
 * register-coloring tie class (cf. func_ov235_020d1a88 ip<->r4). Result is identical; only the
 * scratch-register choice differs.
 */
extern void func_0202ef54(void *out, void *in, void *m);
struct blk4 { int w[4]; };
struct blk11 { int w[11]; };
extern struct blk4 data_ov119_020cc028;

void func_ov119_020cbfc4(int arg0, int self) {
    struct blk4 scratch = data_ov119_020cc028;
    int node = *(int *)(self + 0x390);

    func_0202ef54((void *)(node + 4), (void *)(node + 4), &scratch);
    *(struct blk11 *)(*(int *)(*(int *)(self + 0x3a8)) + 4) =
        *(struct blk11 *)(*(int *)(self + 0x390) + 4);
}
