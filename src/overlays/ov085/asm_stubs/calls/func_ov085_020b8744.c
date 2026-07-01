extern void func_0202a634(void *arg0, void *arg1, int arg2, int arg3);
extern void func_ov085_020b891c(void *arg);
extern int data_ov085_020b9260;
extern void *data_ov085_020b9220;

asm void func_ov085_020b8744(void *arg)
{
    stmfd   sp!, {r4, lr}
    ldr     r0, =data_ov085_020b9260
    mov     r3, #0
    ldr     r4, [r0]
    ldr     r1, =data_ov085_020b9220
    add     r0, r4, #0xc50
    add     r2, r4, #0x2000
    add     r0, r0, #0x2000
    str     r3, [r2, #0xc50]
    str     r3, [r0, #0x10]
    ldrb    r3, [r4, #9]
    add     r0, r0, #0x14
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202a634
    mov     r0, r4
    bl      func_ov085_020b891c
    ldmfd   sp!, {r4, pc}
}
