extern void OS_Terminate(void);
extern void func_0200fa08(void);
extern int data_02046d50[];

asm void func_0200f9ac(int fifoNo, unsigned data)
{
    stmdb sp!, {r3, lr}
    and r0, r1, #0x3f
    cmp r0, #0x11
    bne terminate
    ldr r0, =data_02046d50
    ldr r1, [r0, #0xc]
    cmp r1, #0x0
    ldmneia sp!, {r3, pc}
    ldr r1, [r0, #0x18]
    mov r0, #0x0
    cmp r1, #0x0
    beq after_cb
    blx r1
after_cb:
    cmp r0, #0x0
    beq done
    bl func_0200fa08
done:
    ldr r0, =data_02046d50
    mov r1, #0x1
    str r1, [r0, #0xc]
    ldmia sp!, {r3, pc}
terminate:
    bl OS_Terminate
    ldmia sp!, {r3, pc}
}
