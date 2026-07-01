extern void func_ov219_020d05f0(void);
extern void func_0203c634(void);
extern void func_ov219_020d0d24(void);
extern void func_ov219_020d055c(void);
extern void func_ov107_020c9264(void);

asm void func_ov219_020d0c70(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe5964004
    bl      func_ov219_020d05f0
    dcd     0xe1b01000
    dcd     0x5a000004
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd8070
    dcd     0xe3510b12
    dcd     0xaa000009
    mov r0, #0
    dcd     0xe5840014
    dcd     0xe1d612d0
    dcd     0xe59f2068
    dcd     0xe1a00006
    dcd     0xe3a05001
    bl      func_0203c634
    dcd     0xe1a00006
    bl      func_ov219_020d0d24
    dcd     0xea000009
    dcd     0xe1a00006
    bl      func_ov219_020d055c
    dcd     0xe3500000
    dcd     0x0a000004
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd8070
    dcd     0xe3a05000
    dcd     0xe3550000
    dcd     0xb8bd8070
    dcd     0xe5940044
    dcd     0xe1500005
    dcd     0x08bd8070
    dcd     0xe5845044
    dcd     0xe5940000
    dcd     0xe1a01005
    dcd     0xe3a02001
    bl      func_ov107_020c9264
    dcd     0xe8bd8070
    dcd     func_ov219_020d0d24
}
