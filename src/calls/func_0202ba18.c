/* func_0202ba18 (ARM): if (obj->flags & 4) { func_0202b1c0(&obj->field_c);
 *   obj->flags &= ~4; }
 */
extern void func_0202b1c0(void *p);

asm void func_0202ba18(void *obj)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    ldrb  r0, [r4, #8]
    tst   r0, #4
    ldmeqia sp!, {r4, pc}
    add   r0, r4, #0xc
    bl    func_0202b1c0
    ldrb  r0, [r4, #8]
    bic   r0, r0, #4
    strb  r0, [r4, #8]
    ldmia sp!, {r4, pc}
}
