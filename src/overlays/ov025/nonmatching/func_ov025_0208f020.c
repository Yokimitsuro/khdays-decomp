/* NONMATCHING: branch-vs-predicate. The ROM materialises the shared `mov r0,#1` return up front
 * and predicates the whole first exit (`moveq r1,#0; streq; ldmeq`); mwcc emits a `bne` around a
 * separate 3-instruction block (132B vs 124B). The jump table itself matches. */
/* func_ov025_0208f020 -- filter an incoming ov025 message: swallow it (clear and report handled)
 * when its id equals the panel's current id (ctx+0x209c) or is one of 0x13-0x15 / 0x1b;
 * ids 0x16-0x1a and anything else fall through to the default handler func_020343cc. */
extern int func_ov025_02084afc(void);
extern int func_020343cc(int *msg);

int func_ov025_0208f020(int *param_1) {
    int ctx = func_ov025_02084afc();
    unsigned int id = *(unsigned short *)(*param_1 + 2);
    if (id == *(unsigned int *)(ctx + 0x209c)) {
        *param_1 = 0;
        return 1;
    }
    switch (id) {
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x1b:
        *param_1 = 0;
        return 1;
    }
    return func_020343cc(param_1);
}
