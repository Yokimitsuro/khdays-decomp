/* Equivalent, readable C. NOT byte-exact: matches size and structure EXACTLY
 * except the transform-block load. The original emits one `ldm {r2,r3,ip}`
 * (all three words) then `add r3,#0x900` in-register then three individual
 * `str`; mwcc from this source splits it into `ldmib` (two words) + a separate
 * `ldr` for the first word (+4B). A load-grouping scheduling artifact around the
 * one modified element. The asm stub keeps the blob byte-exact. */
extern void func_ov107_020c5c54(int node, void *blk);
extern int func_0203c634(void *obj, int slot, int arg);

struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };

void func_ov294_020d1f94(void *param_1) {
    int *node_ref = *(int **)((char *)param_1 + 4);
    int node = *node_ref;

    if (((struct hw60 *)(node + 0x60))->lo & 1) {
        int stk[3];
        int *p;
        int a, b, c;
        *(signed char *)(node + 0x1c7) = *(signed char *)(node + 0x1c9);
        p = (int *)node_ref[1];
        a = p[0];
        b = p[1];
        c = p[2];
        stk[0] = a;
        stk[1] = b + 0x900;
        stk[2] = c;
        func_ov107_020c5c54(*node_ref, stk);
        func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), 0);
    }
}
