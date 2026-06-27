extern void *func_ov302_020cbf64(void *, void *);
extern void NNS_FndAppendListObject(void *, void *);

asm void func_ov302_020cc388(void *r0, void *r1, void *r2, void *r3)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    mov     r9, r1
    ldrh    r7, [r9], #2
    mov     r6, #0
    mov     r10, r0
    mov     r11, r2
    mov     r8, r3
    mov     r5, r6
    cmp     r7, #0
    ble     _end
_top:
    mov     r0, r9
    mov     r1, r11
    blx     r8
    cmp     r0, #0
    beq     _skip
    mov     r0, r9
    add     r1, r9, #0x30
    bl      func_ov302_020cbf64
    mov     r4, r0
    mov     r1, r4
    add     r0, r10, #0x18
    bl      NNS_FndAppendListObject
    ldr     r0, [r4, #0x10]
    cmp     r0, #0
    addeq   r0, r6, #1
    moveq   r0, r0, lsl #0x10
    moveq   r6, r0, lsr #0x10
_skip:
    ldrh    r0, [r9]
    add     r5, r5, #1
    cmp     r5, r7
    add     r9, r9, r0
    blt     _top
_end:
    mov     r0, r6
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
