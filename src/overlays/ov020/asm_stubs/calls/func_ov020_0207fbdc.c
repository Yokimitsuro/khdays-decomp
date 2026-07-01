extern int func_ov002_0207687c(void *r0);
extern int func_ov022_02083f0c(void);
extern int func_ov002_0204cb68(void);
extern void func_02023d70(void *r0, int r1, int r2, int r3, int s0);
extern void func_0202a818(void *r0, int r1);
extern void func_0202aa9c(void *r0);
extern void func_02023cc0(int r0);

asm int func_ov020_0207fbdc(void *r0)
{
    stmfd   sp!, {r3, r4, r5, r6, lr}
    sub     sp, sp, #4
    mov     r6, r0
    bl      func_ov002_0207687c
    ldrh    r1, [r6, #0x12]
    mov     r5, r0
    tst     r1, #4
    beq     _end
    bl      func_ov022_02083f0c
    mvn     r1, #0
    cmp     r0, r1
    addeq   sp, sp, #4
    moveq   r0, #0
    ldmeqfd sp!, {r3, r4, r5, r6, pc}
    bl      func_ov002_0204cb68
    ldr     ip, =0x4d9a
    ldr     r1, =0x3b33
    mov     r4, r0
    add     r0, r6, #0x124
    rsb     r2, r1, #0
    rsb     r3, ip, #0
    str     ip, [sp]
    bl      func_02023d70
    mov     r1, r5
    add     r0, r6, #0x1c
    bl      func_0202a818
    add     r0, r6, #0x1c
    bl      func_0202aa9c
    mov     r0, r4
    bl      func_02023cc0
_end:
    mov     r0, #0
    add     sp, sp, #4
    ldmfd   sp!, {r3, r4, r5, r6, pc}
}
