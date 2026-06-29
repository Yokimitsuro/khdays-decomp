extern char data_ov083_020b9b00[];
extern void func_0202afdc(void);
extern void func_ov083_020b9134(void);
extern void func_ov083_020b9330(void);

asm void func_ov083_020b89cc(void)
{
    dcd     0xe92d4038
    dcd     0xe59f1040
    dcd     0xe1a05000
    dcd     0xe5912000
    dcd     0xe2851c0e
    dcd     0xe2820ec3
    dcd     0xe1d11bb0
    dcd     0xe2800a02
    dcd     0xe2824edf
    bl      func_0202afdc
    dcd     0xe2850c2a
    dcd     0xe1d02bfa
    dcd     0xe1a00005
    dcd     0xe2841a02
    bl      func_ov083_020b9134
    dcd     0xe1a00005
    dcd     0xe2841a02
    bl      func_ov083_020b9330
    dcd     0xe8bd8038
    dcd     data_ov083_020b9b00
}
