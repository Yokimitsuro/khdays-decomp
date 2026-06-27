extern void func_0203d194(void *p);

struct Node {
    struct Node *prev;
    struct Node *next;
};

struct List {
    char _0[0x10];
    struct Node *head;  /* offset 0x10 */
    char _14[0xc];
    int count;          /* offset 0x20 */
};

asm void func_01fffc5c(struct List *list)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov r5, r0
    ldr r0, [r5, #0x10]
    cmp r0, r5
    ldmeqia sp!, {r3, r4, r5, pc}
_loop:
    ldr r4, [r0]
    ldr r1, [r0, #4]
    str r1, [r4, #4]
    ldr r2, [r0]
    ldr r1, [r0, #4]
    str r2, [r1]
    bl  func_0203d194
    ldr r1, [r5, #0x20]
    mov r0, r4
    sub r1, r1, #1
    str r1, [r5, #0x20]
    cmp r4, r5
    bne _loop
    ldmia sp!, {r3, r4, r5, pc}
}
