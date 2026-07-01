extern int func_02021980(void *a, void *b);
extern int func_02033b24(int a, int b);

asm void func_02022460(void *a, void *b)
{
    push {r4, r5, r6, lr}
    add r4, r1, #0
    add r5, r0, #0
    bl func_02021980
    add r4, #8
    add r6, r0, #0
    add r0, r5, #0
    add r1, r4, #0
    bl func_02021980
    add r1, r0, #0
    add r0, r6, #0
    bl func_02033b24
    mov r0, #1
    pop {r4, r5, r6, pc}
}
