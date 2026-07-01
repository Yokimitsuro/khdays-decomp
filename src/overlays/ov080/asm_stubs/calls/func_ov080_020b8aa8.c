extern void func_ov080_020b8b64(void);
extern void func_ov080_020b8cdc(void);
extern void func_ov080_020b8fd8(void);
extern void func_ov080_020b9200(void);

asm void func_ov080_020b8aa8(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe1a05001
    dcd     0xe1a04002
    bl      func_ov080_020b8b64
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov080_020b8cdc
    dcd     0xe1a00006
    dcd     0xe1a02004
    dcd     0xe2851e11
    bl      func_ov080_020b8fd8
    dcd     0xe1a00006
    dcd     0xe1a02004
    dcd     0xe2851e22
    bl      func_ov080_020b9200
    dcd     0xe8bd8070
}
