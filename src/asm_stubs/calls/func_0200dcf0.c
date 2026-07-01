extern int data_02046444;

asm void func_0200dcf0(void)
{
    ldr ip, =data_02046444
loop:
    ldr r0, [ip]
    cmp r0, #1
    beq loop
    bx lr
}
