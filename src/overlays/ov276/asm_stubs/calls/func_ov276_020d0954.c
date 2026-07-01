extern void VEC_Add(void);
extern void VEC_Subtract(void);
extern void data_02042258(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c8eb8(void);
extern void func_ov107_020c8fd0(void);
extern void func_ov107_020ca918(void);

asm void func_ov276_020d0954(void) {

    dcd 0xe92d4ff8
    dcd 0xe24dd050
    dcd 0xe58d300c
    dcd 0xe3a03000
    dcd 0xe1a09000
    dcd 0xe1a00003
    dcd 0xe58d0010
    dcd 0xe59d000c
    dcd 0xe58d3014
    dcd 0xe58d1008
    dcd 0xe1a08002
    dcd 0xe3500000
    dcd 0x0a000005
    dcd 0xe5990000
    dcd 0xe59d100c
    dcd 0xe28d2040
    bl func_ov107_020c8fd0
    dcd 0xe58d0014
    dcd 0xea000006
    dcd 0xe3580000
    dcd 0x0a000004
    dcd 0xe5990000
    dcd 0xe28d2040
    dcd 0xe1a01008
    bl func_ov107_020c8eb8
    dcd 0xe58d0014
    dcd 0xe59d0014
    dcd 0xe3a07000
    dcd 0xe3500000
    dcd 0xda000062
    dcd 0xe59f0210
    dcd 0xe28d301c
    dcd 0xe8900007
    dcd 0xe8830007
    dcd 0xe59d0008
    dcd 0xe24d4008
    dcd 0xe20000ff
    dcd 0xe58d0018
    dcd 0xe28d6034
    dcd 0xe28d5028
    dcd 0xe28db040
    dcd 0xe79b0107
    dcd 0xe3a01001
    dcd 0xe1d030b2
    dcd 0xe5d92062
    dcd 0xe1a01311
    dcd 0xe201a0ff
    dcd 0xe112000a
    dcd 0x1a00004b
    dcd 0xe5991000
    dcd 0xe2800074
    dcd 0xe2811074
    dcd 0xe1a02006
    dcd 0xe2811b01
    bl VEC_Subtract
    dcd 0xe1a00006
    dcd 0xe1a01005
    bl func_01ff8d18
    mov r0, #0
    dcd 0xe58d0038
    dcd 0xe1a00006
    dcd 0xe1a01006
    bl func_01ff8d18
    dcd 0xe3500000
    dcd 0x028d001c
    dcd 0x08900007
    dcd 0x08860007
    dcd 0xe3a00b02
    dcd 0xe1a01006
    dcd 0xe1a02006
    bl func_01ffa724
    dcd 0xe5991000
    mov r0, #0
    dcd 0xe58d6000
    dcd 0xe58d0004
    dcd 0xe59d3018
    dcd 0xe79b0107
    dcd 0xe1a02001
    bl func_ov107_020ca918
    dcd 0xe3500000
    dcd 0x0a00002b
    dcd 0xe59d000c
    dcd 0xe3500000
    dcd 0x0a00000d
    dcd 0xe79b0107
    dcd 0xe1a01006
    dcd 0xe2800074
    dcd 0xe1a02005
    bl VEC_Add
    mov r0, #0
    dcd 0xe58d0004
    dcd 0xe8950007
    dcd 0xe8840007
    dcd 0xe5990000
    dcd 0xe3a01004
    dcd 0xe894000c
    bl func_ov107_020c0b90
    dcd 0xea000015
    dcd 0xe3580000
    dcd 0x0a000013
    dcd 0xe598000c
    dcd 0xe1a01005
    dcd 0xe1a02005
    bl func_01ffa724
    dcd 0xe1a00005
    dcd 0xe1a01006
    dcd 0xe1a02005
    bl VEC_Add
    dcd 0xe1a00005
    dcd 0xe1a01008
    dcd 0xe1a02005
    bl VEC_Add
    mov r0, #0
    dcd 0xe58d0004
    dcd 0xe8950007
    dcd 0xe8840007
    dcd 0xe5990000
    dcd 0xe3a01001
    dcd 0xe894000c
    bl func_ov107_020c0b90
    dcd 0xe5d91062
    mov r0, #1
    dcd 0xe58d0010
    dcd 0xe181000a
    dcd 0xe5c90062
    dcd 0xe59d0014
    dcd 0xe2877001
    dcd 0xe1570000
    dcd 0xbaffffa7
    dcd 0xe59d0010
    dcd 0xe3500000
    dcd 0x028dd050
    dcd 0x08bd8ff8
    dcd 0xe59d0008
    dcd 0xe3500005
    dcd 0x908ff100
    dcd 0xea000018
    dcd 0xea000004
    dcd 0xea00000a
    dcd 0xea000010
    dcd 0xea000014
    dcd 0xea000013
    dcd 0xeaffffff
    dcd 0xe5990000
    dcd 0xe599300c
    dcd 0xe3a01f59
    dcd 0xe3a02005
    bl func_ov107_020c5af8
    dcd 0xe28dd050
    dcd 0xe8bd8ff8
    dcd 0xe5990000
    dcd 0xe599300c
    dcd 0xe3a01f59
    dcd 0xe3a02006
    bl func_ov107_020c5af8
    dcd 0xe28dd050
    dcd 0xe8bd8ff8
    dcd 0xe5990000
    dcd 0xe599300c
    dcd 0xe3a01000
    dcd 0xe3a02053
    bl func_ov107_020c5af8
    dcd 0xe28dd050
    dcd 0xe8bd8ff8
    dcd data_02042258
}
