extern char data_027e0000[];
extern void func_01ff81a0(void);

/* NitroSDK IRQ dispatcher entry; callback return continues at func_01ff81a0. */
asm void func_01ff8148(void)
{
    stmdb   sp!, {lr}
    mov     ip, #0x04000000
    add     ip, ip, #0x210
    ldr     r1, [ip, #-8]
    cmp     r1, #0
    ldmeqia sp!, {pc}
    ldmia   ip, {r1, r2}
    ands    r1, r1, r2
    ldmeqia sp!, {pc}
    mov     r3, #0x80000000
selectHighestPriority:
    clz     r0, r1
    bics    r1, r1, r3, lsr r0
    bne     selectHighestPriority
    mov     r1, r3, lsr r0
    str     r1, [ip, #4]
    rsbs    r0, r0, #31
    ldr     r1, =data_027e0000
    ldr     r0, [r1, r0, lsl #2]
    ldr     lr, =func_01ff81a0
    bx      r0
}
