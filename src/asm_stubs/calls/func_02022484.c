/* func_02022484 (THUMB): 3x func_02021980 lookups on consecutive bases
 * (b, b+8, b+0x10), feeding results into func_02033bb4(r6,r7,r2). Returns 1.
 */
extern void *func_02021980(void *a, void *b);
extern void  func_02033bb4(void *a, void *b, void *c);

asm int func_02022484(void *a, void *b)
{
    push  {r3, r4, r5, r6, r7, lr}
    add   r4, r1, #0
    add   r5, r0, #0
    bl    func_02021980
    add   r1, r4, #0
    add   r6, r0, #0
    add   r0, r5, #0
    add   r1, #8
    bl    func_02021980
    add   r4, #0x10
    add   r7, r0, #0
    add   r0, r5, #0
    add   r1, r4, #0
    bl    func_02021980
    add   r2, r0, #0
    add   r0, r6, #0
    add   r1, r7, #0
    bl    func_02033bb4
    mov   r0, #1
    pop   {r3, r4, r5, r6, r7, pc}
}
