extern void func_0201d088(void *p, int a);
extern char data_0204b62c[];

asm void func_0201cb80(int a)
{
    stmdb sp!, {r4, r5, r6, lr}
    ldr r5, =data_0204b62c
    mov r6, r0
    mov r4, #0
loop:
    ldr r0, [r5, #0x110]
    mov r0, r0, lsl #0x1f
    movs r0, r0, asr #0x1f
    beq skip
    mov r0, r5
    mov r1, r6
    bl func_0201d088
skip:
    add r4, r4, #1
    cmp r4, #4
    add r5, r5, #0x174
    blt loop
    ldmia sp!, {r4, r5, r6, pc}
}
