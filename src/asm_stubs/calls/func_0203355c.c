extern void func_0201f750(void);
extern void func_0201ef58(void);
extern int data_0204c234;

asm void func_0203355c(int a)
{
    push {r3, lr}
    add r2, r0, #0
    mov r1, #0
    add r0, sp, #0
    strb r1, [r0]
    lsl r0, r2, #0x10
    add r2, #0x25
    lsl r1, r2, #0x10
    ldr r2, =data_0204c234
    lsr r0, r0, #0x10
    ldr r3, [r2, #0]
    ldr r2, =0x000b04a0
    lsr r1, r1, #0x10
    ldr r2, [r3, r2]
    add r3, sp, #0
    bl func_0201f750
    bl func_0201ef58
    pop {r3, pc}
}
