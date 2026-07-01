extern void func_0201a76c(void *p);
extern void func_0201e144(void *p, int a, int b);
extern void func_0201a8e0(void *p, int a);

asm void func_0201a5b8(void *p, int a)
{
    stmdb sp!, {r4, lr}
    movs r4, r0
    mov r2, r1
    ldrneb r1, [r4, #0x2c]
    cmpne r1, #0
    ldmeqia sp!, {r4, pc}
    cmp r2, #0
    bne not_zero
    bl func_0201a76c
    ldmia sp!, {r4, pc}
not_zero:
    add r0, r4, #0x1c
    mov r1, #0
    bl func_0201e144
    mov r0, r4
    mov r1, #0
    bl func_0201a8e0
    mov r0, #2
    strb r0, [r4, #0x2c]
    ldmia sp!, {r4, pc}
}
