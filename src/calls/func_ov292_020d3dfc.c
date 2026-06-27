extern void *func_01fffd70(void *r0);
extern void *func_01fffd8c(void *r0);

asm void func_ov292_020d3dfc(void *r0)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r6, r0
    ldr     r0, [r6]
    add     r0, r0, #0x394
    bl      func_01fffd70
    cmp     r0, #0
    mov     r5, #0
    beq     _done
    add     r4, r6, #0x1c
_copy:
    ldmia   r0, {r0, r1, r2}
    stmia   r4, {r0, r1, r2}
    ldr     r0, [r6, #0x34]
    cmp     r5, r0
    bge     _done
    ldr     r0, [r6]
    add     r0, r0, #0x394
    bl      func_01fffd8c
    cmp     r0, #0
    add     r5, r5, #1
    bne     _copy
_done:
    mov     r0, #0
    str     r0, [r6, #0x28]
    ldmfd   sp!, {r4, r5, r6, pc}
}
