/* Drain iter callback (caller func_0203c468):
 *   if (item->cb_18 && !item->flag_14) item->cb_18(item);
 *   func_0203d194(item->field_4);          // free aux
 *   func_01fffd0c(ctx, item);              // unlink/free item
 */
extern void func_0203d194(void *p);
extern void func_01fffd0c(void *ctx, void *item);

asm void func_0203c424(void *ctx, void *item)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov   r4, r1
    ldr   r1, [r4, #0x18]
    mov   r5, r0
    cmp   r1, #0
    beq   skip
    ldr   r0, [r4, #0x14]
    cmp   r0, #0
    bne   skip
    mov   r0, r4
    blx   r1
skip:
    ldr   r0, [r4, #4]
    bl    func_0203d194
    mov   r0, r5
    mov   r1, r4
    bl    func_01fffd0c
    ldmia sp!, {r3, r4, r5, pc}
}
