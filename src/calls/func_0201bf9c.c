extern void *func_0201b7e0();
extern int OS_IsThreadAvailable_0x0201b3d8(void);
extern void *func_0201befc();
extern void func_0201b808();
extern void func_0201c2ac();

asm void *func_0201bf9c(void *arg0, void *arg1, int arg2)
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    mov r7, r0
    mov r6, r1
    mov r5, r2
    bl func_0201b7e0
    movs r4, r0
    bne done
    cmp r5, #0
    moveq r2, #0
    beq skip_avail
    bl OS_IsThreadAvailable_0x0201b3d8
    mov r2, r0
skip_avail:
    ldr r1, =func_0201c2ac
    mov r0, r7
    mov r3, r7
    str r6, [sp]
    bl func_0201befc
    mov r4, r0
    cmp r5, #0
    cmpne r4, #0
    beq done
    mov r0, r7
    mov r1, r4
    bl func_0201b808
done:
    mov r0, r4
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
