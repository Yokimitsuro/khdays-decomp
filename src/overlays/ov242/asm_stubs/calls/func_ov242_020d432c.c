extern void func_0203d040(void);
extern void func_0202f188(void);
extern void func_0203c9d0(void);
extern int data_02042264;
extern int data_02041dc8;

asm void func_ov242_020d432c(void)
{
    stmfd   sp!, {r4, lr}
    sub     sp, sp, #0x10
    ldr     r4, [r0, #4]
    mov     r3, #0
    ldr     r2, [r4, #0x28]
    ldmib   r4, {r0, r1}
    bl      func_0203d040
    ldr     r1, =data_02042264
    str     r0, [r4, #4]
    mov     r2, r0
    add     r0, sp, #0
    bl      func_0202f188
    ldr     r0, [r4]
    add     r1, sp, #0
    add     r0, r0, #0xa0
    bl      func_0203c9d0
    ldr     r0, [r4]
    add     ip, r4, #0x10
    add     r3, r0, #0xf0
    ldmia   ip, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, =data_02041dc8
    ldmia   r0, {r0, r1, r2}
    stmia   ip, {r0, r1, r2}
    add     sp, sp, #0x10
    ldmfd   sp!, {r4, pc}
}
