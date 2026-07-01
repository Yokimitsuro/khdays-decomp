extern char data_027e0000[];
extern void INITi_CpuClear32(unsigned int data, void *dst, unsigned int size);

asm void func_01ff8330(void)
{
    mov     ip, #0x4000000
    str     ip, [ip, #0x208]

    ldr     r1, =data_027e0000
    add     r1, r1, #0x3fc0
    add     r1, r1, #0x3c
    mov     r0, #0
    str     r0, [r1]

    ldr     r1, =0x04000180
_wait1:
    ldrh    r0, [r1]
    and     r0, r0, #0xf
    cmp     r0, #1
    bne     _wait1
    mov     r0, #0x100
    strh    r0, [r1]

    mov     r0, #0
    ldr     r3, =0x027ffd9c
    ldr     r4, [r3]
    ldr     r1, =0x027ffd80
    mov     r2, #0x80
    bl      INITi_CpuClear32
    str     r4, [r3]

    ldr     r1, =0x027fff80
    mov     r2, #0x18
    bl      INITi_CpuClear32

    ldr     r1, =0x027fff98
    strh    r0, [r1]

    ldr     r1, =0x027fff9c
    mov     r2, #0x64
    bl      INITi_CpuClear32

    ldr     r1, =0x04000180
_wait2:
    ldrh    r0, [r1]
    and     r0, r0, #0xf
    cmp     r0, #1
    beq     _wait2
    mov     r0, #0
    strh    r0, [r1]

    ldr     r3, =0x027ffe00
    ldr     ip, [r3, #0x24]
    mov     lr, ip
    ldr     r11, =0x027fff80
    ldmia   r11, {r0-r10}
    mov     r11, #0
    bx      ip
}
