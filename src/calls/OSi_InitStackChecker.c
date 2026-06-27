extern unsigned char data_027e0000[];

asm void OSi_InitStackChecker(void)
{
    ldr ip, =data_027e0000
    ldr r3, =0xfddb597d
    add r0, ip, #0x3000
    ldr r2, =0x7bf9dd5b
    ldr r1, =0x800
    str r3, [r0, #0xf7c]
    add r0, ip, #0x3f80
    str r2, [r0, -r1]
    bx lr
}
