extern void func_ov011_0205cad8(void);
extern void func_0203256c(void);
extern void data_ov011_0205e960(void);

asm void func_ov011_0205c370(void)
{
    dcd     0xe92d4008
    bl      func_ov011_0205cad8
    dcd     0xe59f001c
    dcd     0xe5901004
    dcd     0xe5910004
    dcd     0xe3500003
    dcd     0x18bd8008
    dcd     0xe2810f42
    dcd     0xe2800ba1
    bl      func_0203256c
    dcd     0xe8bd8008
    dcd     data_ov011_0205e960
}
