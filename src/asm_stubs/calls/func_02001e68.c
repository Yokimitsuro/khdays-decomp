extern int OS_DisableInterrupts(void);
extern void func_02001ea0(void);
extern int data_0204430c[];

asm void func_02001e68(void) {
    stmdb sp!, {r3, lr}
    ldr r1, =data_0204430c
    ldr r1, [r1, #0x8]
    ldr r3, [r1, #0x0]
    ldr r2, [r3, #0xb4]
    cmp r2, #0x0
    beq done
    mov r1, #0x0
    str r1, [r3, #0xb4]
    blx r2
    bl OS_DisableInterrupts
done:
    bl func_02001ea0
    ldmia sp!, {r3, pc}
}
