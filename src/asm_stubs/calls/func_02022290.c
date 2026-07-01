/* func_02022290 (THUMB): set [r5+0x12c]=1 (constant 0x4b<<2), then call
 * func_02021980(r5,r4) and store result at [r5+0x130] (0x13<<4), then
 * advance r4 by 8 and call func_02021980 again storing at [r5+0x134]
 * (0x4d<<2). Returns 3.
 */
extern void *func_02021980(void *a, void *b);

asm int func_02022290(void *a, void *b)
{
    push  {r3, r4, r5, lr}
    mov   r2, #0x4b
    add   r5, r0, #0
    mov   r3, #1
    lsl   r2, r2, #2
    add   r4, r1, #0
    str   r3, [r5, r2]
    bl    func_02021980
    mov   r1, #0x13
    lsl   r1, r1, #4
    str   r0, [r5, r1]
    add   r4, #8
    add   r0, r5, #0
    add   r1, r4, #0
    bl    func_02021980
    mov   r1, #0x4d
    lsl   r1, r1, #2
    str   r0, [r5, r1]
    mov   r0, #3
    pop   {r3, r4, r5, pc}
}
