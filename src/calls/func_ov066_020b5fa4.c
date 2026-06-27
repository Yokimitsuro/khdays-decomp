extern void func_ov066_020b6150(void *arg0, void *arg1, int arg2);
extern void func_ov066_020b61b0(void *arg0, void *arg1);
extern int data_ov066_020b6b80;

asm void func_ov066_020b5fa4(void *arg)
{
    stmfd   sp!, {r3, r4, r5, lr}
    ldr     r2, =data_ov066_020b6b80
    mov     r5, r0
    add     r1, r5, #0x2a00
    ldr     r3, [r2]
    ldrsh   r2, [r1, #0xba]
    add     r4, r3, #0xc50
    add     r1, r4, #0x2000
    bl      func_ov066_020b6150
    mov     r0, r5
    add     r1, r4, #0x2000
    bl      func_ov066_020b61b0
    ldmfd   sp!, {r3, r4, r5, pc}
}
