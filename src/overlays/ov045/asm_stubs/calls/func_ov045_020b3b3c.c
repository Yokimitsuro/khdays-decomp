extern void *data_ov045_020b4c20;
extern void func_ov045_020b3e38(void);
extern void func_ov045_020b3c5c(void);

asm void func_ov045_020b3b3c(void)
{
    stmfd   sp!, {r3, lr}
    ldr     r2, =data_ov045_020b4c20
    cmp     r1, #0x21
    ldr     r2, [r2]
    mov     r3, #0
    add     r2, r2, #0xdf0
    add     r2, r2, #0x2000
    beq     _eq21
    cmp     r1, #0x22
    ldreq   r3, =func_ov045_020b3e38
    b       _ret
_eq21:
    ldr     r1, [r2, #0x114]
    ldr     r2, [r0, #0x664]
    cmp     r1, #0
    beq     _zero
    mov     r1, #0x30
    blx     r2
    b       _setr3
_zero:
    mov     r1, #0x2f
    blx     r2
_setr3:
    ldr     r3, =func_ov045_020b3c5c
_ret:
    mov     r0, r3
    ldmfd   sp!, {r3, pc}
}
