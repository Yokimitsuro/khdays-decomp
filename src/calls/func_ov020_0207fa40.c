extern int func_02021980();
extern int func_02021948();
extern int func_ov020_0207fc68();
extern int func_ov002_0207643c();

asm int func_ov020_0207fa40(void *a, char *b)
{
    push  {r3, r4, r5, r6, r7, lr}
    add   r4, r1, #0
    add   r5, r0, #0
    bl    func_02021980
    add   r1, r4, #0
    add   r7, r0, #0
    add   r0, r5, #0
    add   r1, #8
    bl    func_02021980
    add   r4, #0x10
    add   r6, r0, #0
    add   r0, r5, #0
    add   r1, r4, #0
    bl    func_02021948
    str   r0, [sp, #0]
    lsl   r0, r6, #0x10
    lsr   r0, r0, #0x10
    add   r1, sp, #0
    bl    func_ov020_0207fc68
    add   r1, r0, #0
    add   r0, r7, #0
    bl    func_ov002_0207643c
    mov   r0, #1
    pop   {r3, r4, r5, r6, r7, pc}
}
