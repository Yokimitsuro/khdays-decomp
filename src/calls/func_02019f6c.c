extern void func_0201a5b8(void *p, int a);
extern char data_0204a320[];

asm void func_02019f6c(int a)
{
    stmdb sp!, {r4, r5, r6, lr}
    ldr r5, =data_0204a320
    mov r6, r0
    mov r4, #0
loop:
    ldrb r0, [r5, #0x2c]
    cmp r0, #0
    beq skip
    mov r0, r5
    mov r1, r6
    bl func_0201a5b8
skip:
    add r4, r4, #1
    cmp r4, #0x10
    add r5, r5, #0x44
    blt loop
    ldmia sp!, {r4, r5, r6, pc}
}
