extern int func_02021980();
extern int func_ov002_0206af88();

asm int func_ov013_0207fe40(void *a, char *b)
{
    push  {r4, r5, r6, r7, lr}
    sub   sp, #0xc
    add   r4, r1, #0
    add   r5, r0, #0
    bl    func_02021980
    add   r1, r4, #0
    add   r6, r0, #0
    add   r0, r5, #0
    add   r1, #8
    bl    func_02021980
    add   r1, r4, #0
    add   r7, r0, #0
    add   r0, r5, #0
    add   r1, #0x10
    bl    func_02021980
    add   r1, r4, #0
    str   r0, [sp, #0]
    add   r0, r5, #0
    add   r1, #0x18
    bl    func_02021980
    add   r4, #0x20
    str   r0, [sp, #4]
    add   r0, r5, #0
    add   r1, r4, #0
    bl    func_02021980
    str   r0, [sp, #8]
    cmp   r6, #0
    bne   _zero
    mov   r0, #1
    b     _go
_zero:
    mov   r0, #0
_go:
    add   r1, r7, #0
    mov   r2, #6
    add   r3, sp, #0
    bl    func_ov002_0206af88
    mov   r0, #1
    add   sp, #0xc
    pop   {r4, r5, r6, r7, pc}
}
