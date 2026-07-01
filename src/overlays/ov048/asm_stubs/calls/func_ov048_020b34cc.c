extern char data_ov048_020b4b80[];
extern void func_ov022_020a384c(void);
extern void func_ov048_020b3a28(void);
extern void func_ov048_020b3bfc(void);
extern void func_ov048_020b3e68(void);
extern void func_ov048_020b3e7c(void);

asm void func_ov048_020b34cc(void)
{
    dcd     0xe92d40f8
    dcd     0xe59f20c0
    dcd     0xe1a06001
    dcd     0xe5921000
    dcd     0xe246202e
    dcd     0xe281102c
    dcd     0xe1a07000
    dcd     0xe3520005
    dcd     0xe2814b0b
    dcd     0xe3e05000
    dcd     0x908ff102
    dcd     0xea000020
    dcd     0xea000004
    dcd     0xea000008
    dcd     0xea00001d
    dcd     0xea00001c
    dcd     0xea00000b
    dcd     0xea00000a
    dcd     0xe59716bc
    dcd     0xe1510006
    dcd     0x0a000017
    bl      func_ov048_020b3a28
    dcd     0xea000015
    dcd     0xe59716bc
    dcd     0xe1510006
    dcd     0x0a000012
    dcd     0xe1a01004
    bl      func_ov048_020b3e68
    dcd     0xea00000f
    dcd     0xe59706bc
    dcd     0xe1500006
    dcd     0x0a00000a
    mov r0, #0
    dcd     0xe5840000
    dcd     0xe3560033
    dcd     0x03a00001
    dcd     0x05840000
    dcd     0xe1a00007
    dcd     0xe1a01004
    bl      func_ov048_020b3bfc
    dcd     0xe1a00007
    dcd     0xe1a01004
    bl      func_ov048_020b3e7c
    dcd     0xe1a05006
    dcd     0xe3a0602f
    dcd     0xe1a00007
    dcd     0xe1a01006
    bl      func_ov022_020a384c
    dcd     0xe3550000
    dcd     0xa58756bc
    dcd     0xe8bd80f8
    dcd     data_ov048_020b4b80
}
