extern void OS_Terminate(void);
extern void func_0200f284(void);
extern int data_02046d40[];

asm void func_0200f220(int fifoNo, unsigned data) {
    stmdb sp!, {r3, lr}
    and r0, r1, #0x3f
    cmp r0, #0x11
    bne terminate
    ldr r1, =data_02046d40
    ldr r0, [r1, #0x0]
    cmp r0, #0x0
    ldmneia sp!, {r3, pc}
    mov r0, #0x1
    str r0, [r1, #0x0]
    ldr r1, [r1, #0x4]
    cmp r1, #0x0
    beq after_cb
    blx r1
after_cb:
    cmp r0, #0x0
    ldmeqia sp!, {r3, pc}
    bl func_0200f284
    ldmia sp!, {r3, pc}
terminate:
    bl OS_Terminate
    ldmia sp!, {r3, pc}
}
