/* func_0201ba08 (ARM): alloc/init-or-rollback helper. Calls func_02010c2c
 * with (ctx[0], (u16)ctx[+0xc]); on failure returns -1. Then calls
 * func_0201bb6c(ctx); if it returns nonzero, decrements (u16)ctx[+0xc]
 * and returns. Else func_02010c7c(ctx[0], 0), returns -1.
 */
extern int func_02010c2c(void *a, int b);
extern int func_0201bb6c(void *ctx);
extern int func_02010c7c(void *a, int b);

asm int func_0201ba08(void *ctx)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    ldrh  r1, [r4, #0xc]
    ldr   r0, [r4]
    bl    func_02010c2c
    cmp   r0, #0
    mvneq r0, #0
    ldmeqia sp!, {r4, pc}
    mov   r0, r4
    bl    func_0201bb6c
    cmp   r0, #0
    ldrneh r0, [r4, #0xc]
    subne r0, r0, #1
    ldmneia sp!, {r4, pc}
    ldr   r0, [r4]
    mov   r1, #0
    bl    func_02010c7c
    mvn   r0, #0
    ldmia sp!, {r4, pc}
}
