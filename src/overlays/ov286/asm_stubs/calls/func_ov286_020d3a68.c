extern void func_ov107_020c89e8(void);

asm int func_ov286_020d3a68(void *arg0, int arg1, void *arg2)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r5, r0
    add     r1, r5, #0x200
    ldrsh   r1, [r1, #0x1a]
    ldr     r4, [r5, #0x214]
    mov     r6, r2
    cmp     r1, #0
    movle   r0, #0
    ldmlefd sp!, {r4, r5, r6, pc}
    mov     r1, r6
    bl      func_ov107_020c89e8
    str     r0, [r6, #0x28]
    add     r1, r5, #0x200
    ldrsh   r2, [r1, #0x1a]
    subs    r0, r2, r0
    movmi   r1, #0
    bmi     _store
    ldrsh   r1, [r1, #0x18]
    cmp     r0, r1
    movle   r1, r0
_store:
    add     r0, r5, #0x200
    strh    r1, [r0, #0x1a]
    ldrsh   r0, [r0, #0x1a]
    cmp     r0, #0
    ldreq   r0, [r4]
    moveq   r1, #3
    streqb  r1, [r0, #0x1c7]
    mov     r0, #1
    ldmfd   sp!, {r4, r5, r6, pc}
}
