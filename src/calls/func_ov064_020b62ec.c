extern int *data_ov064_020b7420;
extern void func_0202afdc(void *arg0, int arg1);
extern void func_ov064_020b6a54(void *arg0, void *arg1, int arg2);
extern void func_ov064_020b6c50(void *arg0, void *arg1);

asm void func_ov064_020b62ec(void *arg)
{
    stmdb   sp!, {r3, r4, r5, lr}
    ldr     r1, =data_ov064_020b7420
    mov     r5, r0
    ldr     r2, [r1]
    add     r1, r5, #0xe00
    add     r0, r2, #0xc30
    ldrh    r1, [r1, #0xb0]
    add     r0, r0, #0x2000
    add     r4, r2, #0xdf0
    bl      func_0202afdc
    add     r0, r5, #0x2a00
    ldrsh   r2, [r0, #0xba]
    mov     r0, r5
    add     r1, r4, #0x2000
    bl      func_ov064_020b6a54
    mov     r0, r5
    add     r1, r4, #0x2000
    bl      func_ov064_020b6c50
    ldmia   sp!, {r3, r4, r5, pc}
}
