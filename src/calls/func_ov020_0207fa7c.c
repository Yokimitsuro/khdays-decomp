extern int func_02021980();
extern int func_ov002_02076468();
extern int func_ov020_0207fcd4();

asm int func_ov020_0207fa7c(void *a, char *b)
{
    push  {r3, r4, r5, r6, r7, lr}
    add   r5, r1, #0
    add   r4, r0, #0
    bl    func_02021980
    add   r1, r5, #0
    add   r7, r0, #0
    add   r0, r4, #0
    add   r1, #8
    bl    func_02021980
    add   r1, r5, #0
    add   r6, r0, #0
    add   r0, r4, #0
    add   r1, #0x10
    bl    func_02021980
    add   r4, r0, #0
    ldr   r5, [r5, #0x1c]
    add   r0, r7, #0
    bl    func_ov002_02076468
    lsr   r1, r5, #0x10
    lsl   r1, r1, #0x10
    lsr   r1, r1, #0x10
    lsl   r1, r1, #0x18
    lsr   r1, r1, #0x18
    str   r1, [sp, #0]
    lsl   r1, r6, #0x10
    lsl   r2, r4, #0x10
    lsl   r3, r5, #0x10
    lsr   r1, r1, #0x10
    lsr   r2, r2, #0x10
    lsr   r3, r3, #0x10
    bl    func_ov020_0207fcd4
    mov   r0, #1
    pop   {r3, r4, r5, r6, r7, pc}
}
