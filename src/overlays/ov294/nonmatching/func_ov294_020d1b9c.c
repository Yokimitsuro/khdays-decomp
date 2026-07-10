/* Equivalent, readable C. NOT byte-exact: size and structure match EXACTLY;
 * the sole difference is the documented ip<->lr swap on the >16-byte struct
 * copy's writeback pointers — mwcc colors src->ip, dst->lr for `ldm src!/stm
 * dst!` chains, but the original uses the opposite (src->lr, dst->ip).
 * Unsteerable across pointer declaration order. The asm stub keeps it byte-exact. */
extern void func_ov107_020c6980(void *obj);

struct mtx11 { int m[11]; };

void func_ov294_020d1b9c(void *param_1) {
    func_ov107_020c6980(param_1);
    *(struct mtx11 *)(**(int **)((char *)param_1 + 0x388) + 0x10) =
        *(struct mtx11 *)(*(int *)((char *)param_1 + 0x384) + 0x30);
    *(struct mtx11 *)(*(int *)((char *)param_1 + 0x390) + 0x10) =
        *(struct mtx11 *)(*(int *)((char *)param_1 + 0x384) + 0x30);
}
