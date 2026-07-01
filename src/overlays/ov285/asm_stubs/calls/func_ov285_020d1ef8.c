extern void *func_0203d040(int r0, int r1, int r2, int r3);
extern void func_0202f188(void *r0, void *r1, void *r2);
extern void func_0202ed60(void *r0, void *r1, void *r2);
extern void func_0202ef54(void *r0, void *r1, void *r2);
extern void func_0203c9d0(void *r0, void *r1);
extern char data_02042264[];
extern char data_02041dc8[];

asm void func_ov285_020d1ef8(void *r0)
{
    stmfd   sp!, {r4, lr}
    sub     sp, sp, #0x20
    ldr     r4, [r0, #4]
    mov     r3, #0
    ldr     r2, [r4, #0x14]
    ldmib   r4, {r0, r1}
    bl      func_0203d040
    ldr     r1, =data_02042264
    str     r0, [r4, #4]
    mov     r2, r0
    add     r0, sp, #0x10
    bl      func_0202f188
    ldr     r2, [r4]
    ldr     r1, =data_02042264
    add     r0, sp, #0
    add     r2, r2, #0x124
    bl      func_0202ed60
    add     r0, sp, #0
    add     r2, sp, #0x10
    mov     r1, r0
    bl      func_0202ef54
    ldr     r0, [r4]
    add     r1, sp, #0
    add     r0, r0, #0xa0
    bl      func_0203c9d0
    ldr     r0, [r4]
    add     lr, r4, #0x1c
    add     ip, r0, #0xf0
    ldmia   lr, {r0, r1, r2}
    stmia   ip, {r0, r1, r2}
    ldr     r3, =data_02041dc8
    ldmia   r3, {r0, r1, r2}
    stmia   lr, {r0, r1, r2}
    add     sp, sp, #0x20
    ldmfd   sp!, {r4, pc}
}
