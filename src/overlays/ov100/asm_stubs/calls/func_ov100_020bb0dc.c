extern void data_ov100_020bc1c0(void);
extern void func_ov100_020bb3d8(void);
extern void func_ov100_020bb1fc(void);

asm void func_ov100_020bb0dc(void)
{
    stmdb   sp!, {r3, lr}
    ldr     r2, =data_ov100_020bc1c0
    cmp     r1, #0x21
    ldr     r2, [r2]
    mov     r3, #0
    add     r2, r2, #0xdf0
    add     r2, r2, #0x2000
    beq     handle_21
    cmp     r1, #0x22
    ldreq   r3, =func_ov100_020bb3d8
    b       done
handle_21:
    ldr     r1, [r2, #0x114]
    ldr     r2, [r0, #0x664]
    cmp     r1, #0
    beq     no_flag
    mov     r1, #0x30
    blx     r2
    b       load_result
no_flag:
    mov     r1, #0x2f
    blx     r2
load_result:
    ldr     r3, =func_ov100_020bb1fc
done:
    mov     r0, r3
    ldmia   sp!, {r3, pc}
}
