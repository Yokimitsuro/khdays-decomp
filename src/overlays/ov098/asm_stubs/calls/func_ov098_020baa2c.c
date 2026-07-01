extern void func_ov022_0209fb60(void *, int, int);
extern void func_ov022_0209fb98(void *, int, int);

asm void func_ov098_020baa2c(char *)
{
    push {r4, lr}
    add r4, r0, #0
    mov r1, #0
    mov r2, #1
    bl func_ov022_0209fb60
    add r0, r4, #0
    mov r1, #0
    mov r2, #1
    bl func_ov022_0209fb98
    ldr r1, =0xda9
    ldrsb r0, [r4, r1]
    cmp r0, #0
    beq done
    sub r0, r1, #1
    ldrb r2, [r4, r0]
    mov r0, #1
    orr r2, r0
    sub r0, r1, #1
    strb r2, [r4, r0]
done:
    pop {r4, pc}
}
