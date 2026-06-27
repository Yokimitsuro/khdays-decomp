extern int func_ov002_02072aa0();
extern char data_ov013_0207fec0[];

asm void func_ov013_0207fbe4(void *a, int b, char *c)
{
    push  {r4, r5, r6, lr}
    add   r3, r1, #0
    mov   r1, #0x11
    lsl   r1, r1, #4
    ldrsb r4, [r2, r1]
    mov   r0, #0
    cmp   r4, #0
    ble   _end
    add   r1, r1, #4
    add   r1, r2, r1
    mov   r2, #0x43
    lsl   r2, r2, #2
    sub   r5, r2, #3
_lp:
    ldrsb r6, [r1, r5]
    cmp   r6, #1
    bne   _next
    mov   r2, #0x42
    lsl   r2, r2, #2
    ldrb  r4, [r1, r2]
    mov   r0, #1
    bic   r4, r0
    strb  r4, [r1, r2]
    b     _end
_next:
    add   r0, r0, #1
    add   r1, r1, r2
    cmp   r0, r4
    blt   _lp
_end:
    ldr   r0, =data_ov013_0207fec0
    mov   r1, #5
    mov   r2, #0
    bl    func_ov002_02072aa0
    pop   {r4, r5, r6, pc}
}
