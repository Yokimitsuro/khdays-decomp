extern int func_02021980(void *a, void *b);
extern int func_02034014(int a);
extern int func_02033fb4(int a, int b);

asm void func_020224ec(void *a, void *b)
{
    push {r4, lr}
    bl func_02021980
    add r4, r0, #0
    mov r0, #0
    bl func_02034014
    cmp r0, #0
    beq lbl
    mov r0, #0
    pop {r4, pc}
lbl:
    mov r0, #0
    add r1, r4, #0
    bl func_02033fb4
    mov r0, #1
    pop {r4, pc}
}
