typedef unsigned short u16;
typedef unsigned int u32;

extern u16 data_020422b4;
extern u16 data_020446d0;

asm void func_020056b4(register u32 arg0, register u32 arg1, register u32 arg2)
{
    stmdb sp!, {r3, lr}
    ldr     r3, =data_020422b4
    mov     lr, #0x04000000
    ldrh    ip, [r3]
    ldr     lr, [lr]
    ldr     r3, =data_020446d0
    cmp     ip, #0
    strh    r0, [r3]
    ldr     r3, =0xfff0fff0
    moveq   r0, #0
    and     r3, lr, r3
    orr     r0, r3, r0, lsl #16
    orr     r0, r1, r0
    orr     r1, r0, r2, lsl #3
    mov     ip, #0x04000000
    ldr     r0, =data_020446d0
    str     r1, [ip]
    ldrh    r0, [r0]
    cmp     r0, #0
    ldreq   r0, =data_020422b4
    moveq   r1, #0
    streqh  r1, [r0]
    ldmia   sp!, {r3, pc}
}
