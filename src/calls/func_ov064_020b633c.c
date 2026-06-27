extern int *data_ov064_020b7420;
extern void *func_ov064_020b6638(void);
extern void *func_ov064_020b645c(void);

asm void *func_ov064_020b633c(void *arg0, int arg1)
{
    stmdb   sp!, {r3, lr}
    ldr     r2, =data_ov064_020b7420
    cmp     r1, #0x21
    ldr     r2, [r2]
    mov     r3, #0
    add     r2, r2, #0xdf0
    add     r2, r2, #0x2000
    beq     _case_21
    cmp     r1, #0x22
    ldreq   r3, =func_ov064_020b6638
    b       _return
_case_21:
    ldr     r1, [r2, #0x114]
    ldr     r2, [r0, #0x664]
    cmp     r1, #0
    beq     _call_2f
    mov     r1, #0x30
    blx     r2
    b       _load_645c
_call_2f:
    mov     r1, #0x2f
    blx     r2
_load_645c:
    ldr     r3, =func_ov064_020b645c
_return:
    mov     r0, r3
    ldmia   sp!, {r3, pc}
}
