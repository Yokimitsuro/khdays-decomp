extern void *func_ov302_020cbf64(void *, void *);
extern void NNS_FndAppendListObject(void *, void *);

asm void func_ov302_020cc424(void *r0, void *r1, int r2)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    ldrh    r7, [r1], #2
    mov     r5, #0
    mov     r4, r0
    mov     r6, r5
    mov     r0, r5
    mov     lr, r5
    cmp     r7, #0
    ble     _end
    add     ip, r2, #1
_top:
    ldrh    r8, [r1, #6]
    cmp     r8, ip
    ldrlsh  r3, [r1, #8]
    cmpls   ip, r3
    bls     _maybe
    cmp     r2, r8
    bhs     _next
_maybe:
    cmp     r0, #0
    beq     _set
    ldrh    r3, [r0, #6]
    cmp     r8, r3
    bhs     _next
_set:
    mov     r0, r1
    add     r6, r1, #0x30
_next:
    ldrh    r3, [r1]
    add     lr, lr, #1
    cmp     lr, r7
    add     r1, r1, r3
    blt     _top
_end:
    cmp     r0, #0
    beq     _ret
    mov     r1, r6
    bl      func_ov302_020cbf64
    mov     r1, r0
    add     r0, r4, #0x18
    bl      NNS_FndAppendListObject
    mov     r5, #1
_ret:
    mov     r0, r5
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
}
