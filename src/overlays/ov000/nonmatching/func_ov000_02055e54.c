/* func_ov000_02055e54 -- run a handler over every object in a logo list, ov000.
 * NONMATCHING: CSE tie. The retail build recomputes the list head (ctx+0x238) for
 * the loop instead of holding it across the first list call (-1 instr in ours).
 * Logic is exact. For the port.
 * Walks the NNS list @ctx+0x4a38, invoking func_ov000_02055e10(ctx, obj, arg) per node. */
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void func_ov000_02055e10(void *ctx, void *obj, int arg);
void func_ov000_02055e54(void *ctx, int arg) {
    void *obj = NNS_FndGetNextListObject((char *)ctx + 0x4a38, 0);
    while (obj != 0) {
        func_ov000_02055e10(ctx, obj, arg);
        obj = NNS_FndGetNextListObject((char *)ctx + 0x4a38, obj);
    }
}
