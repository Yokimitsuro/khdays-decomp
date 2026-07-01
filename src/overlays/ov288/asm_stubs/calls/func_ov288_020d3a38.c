extern void func_0203c7e8(void *r0);
extern void NNSi_FndDestroyDoubleList(void *r0);
extern void func_ov107_020c68ec(void *r0);

asm void func_ov288_020d3a38(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r0, [r5, #0x384]
    bl      func_0203c7e8
    mov     r4, #0
_020d3a38_loop:
    add     r0, r5, r4, lsl #3
    ldr     r0, [r0, #0x3c0]
    cmp     r0, #0
    beq     _020d3a38_next
    bl      func_0203c7e8
_020d3a38_next:
    add     r4, r4, #1
    cmp     r4, #2
    blt     _020d3a38_loop
    add     r0, r5, #0x398
    bl      NNSi_FndDestroyDoubleList
    mov     r0, r5
    bl      func_ov107_020c68ec
    ldmfd   sp!, {r3, r4, r5, pc}
}
