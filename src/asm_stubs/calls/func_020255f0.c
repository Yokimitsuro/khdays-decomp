/* func_020255f0 (ARM): if func_020255d4(r0, 7, 0) and func_02017088() both
 * non-null, computes p = ret_02017088 + ret_02017088->[+0x14], then calls
 * func_02023768(r5, r6, p - r6, r4). Uses unusual `movs r2, r0` to set Z too.
 */
extern int  func_020255d4(void *a, int b, int c);
extern void *func_02017088(void);
extern void func_02023768(void *a, void *b, int c, void *d);

asm void func_020255f0(void *a, void *b, void *c)
{
    stmdb sp!, {r4, r5, r6, lr}
    mov   r5, r1
    mov   r4, r2
    mov   r1, #7
    mov   r2, #0
    mov   r6, r0
    bl    func_020255d4
    cmp   r0, #0
    ldmeqia sp!, {r4, r5, r6, pc}
    bl    func_02017088
    movs  r2, r0
    ldmeqia sp!, {r4, r5, r6, pc}
    ldr   r1, [r2, #0x14]
    mov   r0, r5
    add   r2, r2, r1
    mov   r1, r6
    mov   r3, r4
    sub   r2, r2, r6
    bl    func_02023768
    ldmia sp!, {r4, r5, r6, pc}
}
