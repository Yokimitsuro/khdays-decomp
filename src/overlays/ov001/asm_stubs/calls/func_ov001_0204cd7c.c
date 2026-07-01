extern void func_02005414(void);
extern void func_020054b0(void);
extern void func_020030e4(void);
extern void func_0200d608(void);
extern void func_0200e18c(int, int);
extern void func_02005630(void);
extern void func_0201e374(int);
extern void func_0201e3cc(int);
extern void func_02011594(void *, int);
extern void func_02000f1c(void);
extern void OS_EnableIrqMask(int);
extern void func_ov001_0204cf5c(void);
extern void func_ov001_0204cac0(void);
extern void func_ov001_0204cbb4(void);
extern void func_ov001_0204cb6c(void);
extern void func_ov001_0204cccc(void);
extern int data_020422b8;
extern int data_0204be24;

asm void func_ov001_0204cd7c(void)
{
    stmdb sp!, {r3, lr}
    bl    func_02005414
    ldr   ip, =0x04000304
    ldr   r0, =0xfffffdf1
    ldrh  r3, [ip]
    ldr   r1, =data_020422b8
    mov   r2, #1
    and   r0, r3, r0
    orr   r0, r0, #0xe
    orr   r0, r0, #0x200
    strh  r0, [ip]
    str   r2, [r1]
    bl    func_020054b0
    bl    func_020030e4
    bl    func_0200d608
    mov   r0, #0x500
    mov   r1, #0x2400
    bl    func_0200e18c
    bl    func_02005630
    ldr   r2, =0x04001000
    mov   r0, #0x10
    ldr   r1, [r2]
    bic   r1, r1, #0x10000
    str   r1, [r2]
    bl    func_0201e374
    mov   r0, #0x10
    bl    func_0201e3cc
    ldr   r0, =data_0204be24
    mov   r1, #0x20
    bl    func_02011594
    bl    func_02000f1c
    mov   r0, #0x40000
    bl    OS_EnableIrqMask
    ldr   r2, =0x04000208
    mov   r0, #1
    ldrh  r1, [r2]
    strh  r0, [r2]
    bl    func_ov001_0204cf5c
    bl    func_ov001_0204cac0
    bl    func_ov001_0204cbb4
    bl    func_ov001_0204cb6c
    bl    func_ov001_0204cccc
    ldmia sp!, {r3, pc}
}
