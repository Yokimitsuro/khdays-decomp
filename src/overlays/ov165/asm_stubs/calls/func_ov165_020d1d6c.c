extern void func_ov107_020c08cc(void);
extern void func_ov107_020c09a0(void);
extern void func_ov107_020c0b14(void);
extern void func_ov107_020c7500(void);
extern void func_ov107_020cb040(void);
extern void func_ov165_020d46ac(void);
extern void func_ov165_020d4898(void);

asm void func_ov165_020d1d6c(void) {

    dcd 0xe92d4070
    dcd 0xe24dd008
    dcd 0xe1a05001
    dcd 0xe5d51002
    dcd 0xe1a06000
    dcd 0xe1a04002
    dcd 0xe3510005
    dcd 0x1a000045
    dcd 0xe5d51003
    dcd 0xe3510004
    dcd 0x908ff101
    dcd 0xea000041
    dcd 0xea000003
    dcd 0xea000013
    dcd 0xea00003e
    dcd 0xea00001e
    dcd 0xea00002d
    dcd 0xe59613c4
    dcd 0xe5911004
    dcd 0xe3510000
    dcd 0x1a000002
    bl func_ov165_020d4898
    dcd 0xe59613c4
    dcd 0xe5810004
    dcd 0xe59603c0
    dcd 0xe59f10e4
    dcd 0xe2802004
    dcd 0xe1a00006
    dcd 0xe58d2000
    dcd 0xe3a02004
    dcd 0xe3a03000
    bl func_ov107_020cb040
    dcd 0xe58603d0
    dcd 0xea00002b
    dcd 0xe3a00a01
    dcd 0xe58d0000
    dcd 0xe2850005
    dcd 0xe58d0004
    dcd 0xe59613c4
    dcd 0xe596003c
    dcd 0xe5911008
    dcd 0xe3a02005
    dcd 0xe3a03000
    bl func_ov107_020c08cc
    dcd 0xe59613c4
    dcd 0xe581000c
    dcd 0xea00001e
    dcd 0xe3a00b06
    dcd 0xe58d0000
    dcd 0xe2850005
    dcd 0xe58d0004
    dcd 0xe59613c4
    dcd 0xe5d53004
    dcd 0xe596003c
    dcd 0xe5911010
    dcd 0xe3a02005
    bl func_ov107_020c08cc
    dcd 0xe59623c4
    dcd 0xe3a01001
    dcd 0xe5820014
    dcd 0xe1a00006
    bl func_ov107_020c0b14
    dcd 0xea00000e
    bl func_ov165_020d46ac
    dcd 0xe59623c4
    dcd 0xe3a01000
    dcd 0xe582001c
    dcd 0xe58d1000
    mov r0, #1
    dcd 0xe58d0004
    dcd 0xe59613c4
    dcd 0xe596003c
    dcd 0xe5911020
    dcd 0xe2863fe5
    dcd 0xe3a02015
    bl func_ov107_020c09a0
    dcd 0xe59613c4
    dcd 0xe5810024
    dcd 0xe1a00006
    dcd 0xe1a01005
    dcd 0xe1a02004
    bl func_ov107_020c7500
    dcd 0xe28dd008
    dcd 0xe8bd8070
    dcd 0x00000153
}
