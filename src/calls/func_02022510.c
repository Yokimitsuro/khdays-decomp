/* func_02022510 (THUMB): r6=func_02021980(r5,r1); func_02021948(r5,r1+8);
 * id=func_02024ee8(0xf); store id at (*(u32*)((r5[0x128]) + r6*4)) + 0x48c.
 * Returns 1.
 */
extern void *func_02021980(void *a, void *b);
extern void  func_02021948(void *a, void *b);
extern int   func_02024ee8(int x);

asm int func_02022510(void *a, void *b)
{
    push  {r4, r5, r6, lr}
    add   r4, r1, #0
    add   r5, r0, #0
    bl    func_02021980
    add   r4, #8
    add   r6, r0, #0
    add   r0, r5, #0
    add   r1, r4, #0
    bl    func_02021948
    mov   r1, #0xf
    bl    func_02024ee8
    mov   r1, #0x4a
    lsl   r1, r1, #2
    ldr   r2, [r5, r1]
    lsl   r1, r6, #2
    add   r2, r2, r1
    ldr   r1, =0x0000048c
    str   r0, [r2, r1]
    mov   r0, #1
    pop   {r4, r5, r6, pc}
}
