extern void func_02031130(void);
extern void func_01fffac0(void *p);

struct Root0203158c {
    int field_0;
    char *field_4;
};

extern struct Root0203158c *data_0204c230;

asm void func_0203158c(int idx)
{
    stmdb sp!, {r3, r4, r5, lr}
    ldr r1, =data_0204c230
    mov r5, r0
    ldr r4, [r1]
    ldr r1, [r4]
    cmp r1, #0
    ldmneia sp!, {r3, r4, r5, pc}
    bl func_02031130
    ldr r0, [r4, #4]
    add r0, r0, r5, lsl #5
    bl func_01fffac0
    ldmia sp!, {r3, r4, r5, pc}
}
