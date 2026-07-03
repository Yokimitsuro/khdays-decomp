/* func_ov214_020cd78c (x5 family: ov215/216/217/264/276) — NON-MATCHING.
 * Semantically exact. Sole diff: the `if(func_ov214_020cd0e8(node,d)==0){ [0x1c7]=4;
 * return; }` block is PREDICATED in the original (cmp;ldreq;moveq;strbeq;addeq;popeq),
 * but mwcc emits a `bne` branch around it (+1 instr, 192 vs 188). Tried both structural
 * forms (early-return / if-else) and both pointer stylings (int state / int *state);
 * mwcc always branches. Branch-vs-predicate heuristic tie (see codegen-steering memory,
 * the "unsteerable" class). asm stub stays byte-exact via dsd. */
extern int func_ov107_020cab14(int a, int b);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_01ff8d18(void *a, void *b);
extern int func_020050b4(int x, int z);
extern int func_ov214_020cd0e8(void *node, int arg);
extern void func_0203c634(void *node, int slot, void *cb);

void func_ov214_020cd78c(int *node) {
    int *state = (int *)node[1];
    int buf[3];
    int target = func_ov107_020cab14(*state, 0);
    state[2] = target;
    if (target == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 8), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)(*state + 0xb0), buf);
    {
        int d = func_01ff8d18(buf, buf);
        state[0x13] = func_020050b4(buf[0], buf[2]);
        if (func_ov214_020cd0e8(node, d) == 0) {
            *(signed char *)(*state + 0x1c7) = 4;
            return;
        }
    }
    func_0203c634(node, *(signed char *)(node + 8), 0);
}
