extern void *func_0203d15c(int);
extern void OS_SPrintf(void *, int);
extern int func_ov107_020c9c24(void *);
extern void func_ov107_020c6624(void *, int);
extern int data_ov294_020d2520;
extern void func_ov294_020d1a24(void *p);

asm void func_ov294_020d1998(int arg)
{
    stmfd   sp!, {r3, r4, r5, lr}
    sub     sp, sp, #0x20
    mov     r5, r0
    add     r2, sp, #0
    mov     r0, #7
    mov     r1, #0
_loop:
    strb    r1, [r2]
    strb    r1, [r2, #1]
    strb    r1, [r2, #2]
    strb    r1, [r2, #3]
    add     r2, r2, #4
    subs    r0, r0, #1
    bne     _loop
    mov     r0, #0x394
    strb    r1, [r2]
    bl      func_0203d15c
    mov     r4, r0
    mov     r2, #0x70
    ldr     r1, =data_ov294_020d2520
    add     r0, sp, #0
    strb    r2, [r4, #0x19c]
    bl      OS_SPrintf
    add     r0, sp, #0
    bl      func_ov107_020c9c24
    str     r0, [r4, #0x1a4]
    ldr     r2, =func_ov294_020d1a24
    mov     r0, r4
    mov     r1, r5
    str     r2, [r4, #0x18c]
    bl      func_ov107_020c6624
    mov     r0, r4
    add     sp, sp, #0x20
    ldmfd   sp!, {r3, r4, r5, pc}
}
