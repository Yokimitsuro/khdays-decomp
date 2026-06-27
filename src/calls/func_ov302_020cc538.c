extern void NNS_FndGetNextListObject(void);
extern void NNS_FndRemoveListObject(void);
extern void func_ov302_020cc0ac(void);
extern void NNSi_FndFreeFromDefaultHeap(void);

asm void func_ov302_020cc538(void)
{
    stmdb   sp!, {r4, r5, r6, lr}
    mov     r6, r0
    add     r0, r6, #0x18
    mov     r1, #0
    bl      NNS_FndGetNextListObject
    movs    r4, r0
    ldmeqia sp!, {r4, r5, r6, pc}
_loop:
    mov     r1, r4
    add     r0, r6, #0x18
    bl      NNS_FndGetNextListObject
    mov     r5, r0
    mov     r0, r4
    bl      func_ov302_020cc0ac
    mov     r1, r4
    add     r0, r6, #0x18
    bl      NNS_FndRemoveListObject
    cmp     r4, #0
    beq     _skip
    mov     r0, r4
    bl      NNSi_FndFreeFromDefaultHeap
_skip:
    mov     r4, r5
    cmp     r5, #0
    bne     _loop
    ldmia   sp!, {r4, r5, r6, pc}
}
