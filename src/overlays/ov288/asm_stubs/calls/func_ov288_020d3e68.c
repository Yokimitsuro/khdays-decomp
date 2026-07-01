extern void NNSi_FndDestroyDoubleList(void *r0);
extern void func_01fffc24(void *r0);
extern void *func_01fffca8(void *r0, int r1, int r2);

asm void func_ov288_020d3e68(void *r0, int r1, void *r2)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, sb, lr}
    mov     r6, r0
    ldr     r3, [r2]
    add     r0, r6, #0x398
    mov     r5, r1
    str     r3, [r6, #0x390]
    add     r4, r2, #4
    bl      NNSi_FndDestroyDoubleList
    add     r0, r6, #0x398
    bl      func_01fffc24
    ldr     r0, =0xaaaaaaab
    sub     r1, r5, #4
    umull   r0, r5, r1, r0
    mov     r5, r5, lsr #3
    mov     sb, #0
    cmp     r5, #0
    ldmlefd sp!, {r3, r4, r5, r6, r7, r8, sb, pc}
    mov     r8, #0xc
    mov     r7, #0x64
_020d3e68_loop:
    mov     r1, r8
    mov     r2, r7
    add     r0, r6, #0x398
    bl      func_01fffca8
    mov     r3, r0
    ldmia   r4, {r0, r1, r2}
    add     sb, sb, #1
    stmia   r3, {r0, r1, r2}
    cmp     sb, r5
    add     r4, r4, #0xc
    blt     _020d3e68_loop
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, sb, pc}
}
