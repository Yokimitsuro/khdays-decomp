extern void MI_CpuFill8(void);
extern void NNS_FndInitList(void);
extern void func_ov002_0205280c(void);
extern void func_0201ef9c(void);
extern void func_ov302_020cc598(void);
extern void data_ov302_020cc740(void);

asm void func_ov302_020cc64c(void)
{
    stmdb   sp!, {r3, r4, r5, lr}
    mov     r4, r1
    mov     r5, r0
    mov     r1, #0
    mov     r2, #0x24
    bl      MI_CpuFill8
    add     r0, r5, #0x18
    mov     r1, #0x4c
    bl      NNS_FndInitList
    ldr     r1, =data_ov302_020cc740
    mov     r0, r5
    bl      func_ov002_0205280c
    ldr     r0, [r4, #8]
    mov     r1, #0xe
    str     r0, [r5, #0xc]
    ldr     r0, [r4]
    bl      func_0201ef9c
    str     r0, [r5, #0x14]
    mov     r0, r5
    ldr     r1, [r4, #8]
    ldr     r2, [r4, #4]
    bl      func_ov302_020cc598
    ldmia   sp!, {r3, r4, r5, pc}
}
