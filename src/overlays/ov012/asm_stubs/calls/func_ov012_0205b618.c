extern void NNSi_FndGetCurrentRootHeap(void);
extern void OS_IsThreadAvailable(void);
extern void OS_WaitVBlankIntr(void);
extern void func_02005630(void);
extern void func_0200566c(void);
extern void func_0200d49c(void);
extern void func_0201e374(void);
extern void func_0201e3cc(void);
extern void func_0201e428(void);
extern void func_0201e438(void);
extern void func_02020cc8(void);
extern void func_02020e58(void);
extern void func_02021048(void);
extern void func_02030e64(void);
extern void func_02031574(void);
extern void func_ov012_0205b280(void);
extern void func_ov012_0205b584(void);
extern void func_ov012_0205b8ac(void);
extern void func_ov024_02084b14(void);
extern void func_ov024_02084db8(void);

asm void func_ov012_0205b618(void)
{
    dcd     0xe92d4ff8
    bl      NNSi_FndGetCurrentRootHeap
    dcd     0xe1a08000
    dcd     0xe1d800b2
    dcd     0xe3100002
    dcd     0x1a00007b
    dcd     0xe2880902
    dcd     0xe5901bd8
    dcd     0xe3510002
    dcd     0x15900bdc
    dcd     0x13500002
    dcd     0x1a000075
    bl      OS_IsThreadAvailable
    dcd     0xe1a09000
    dcd     0xe1a0a009
    bl      func_ov024_02084db8
    dcd     0xe3500000
    dcd     0x1a000057
    dcd     0xe59fb234
    dcd     0xe59f7234
    dcd     0xe59f4234
    dcd     0xe2885902
    dcd     0xe1d800b2
    dcd     0xe3100004
    dcd     0x0a000008
    bl      func_ov012_0205b280
    dcd     0xe3500000
    dcd     0x0a00001b
    dcd     0xe1d800b2
    dcd     0xe3100001
    dcd     0x0a00004a
    dcd     0xe2880004
    bl      func_02021048
    dcd     0xea000047
    dcd     0xe5d50be0
    dcd     0xe3500000
    dcd     0x1a000012
    dcd     0xe1db20b0
    dcd     0xe1d710b0
    dcd     0xe5950bec
    dcd     0xe1821001
    dcd     0xe3500000
    dcd     0xe0210004
    dcd     0xe0000004
    dcd     0xe1a00800
    dcd     0xe1a00820
    dcd     0xe2001008
    dcd     0x1a000006
    dcd     0xe3510000
    dcd     0x0a000004
    dcd     0xe3a00000
    dcd     0xe5850be8
    dcd     0xe1d800b2
    dcd     0xe3800004
    dcd     0xe1c800b2
    dcd     0xe5851bec
    dcd     0xe1d800b2
    dcd     0xe3100001
    dcd     0x0a000005
    dcd     0xe2880004
    bl      func_02020e58
    dcd     0xe3500000
    dcd     0x01d800b2
    dcd     0x03c00001
    dcd     0x01c800b2
    bl      OS_IsThreadAvailable
    dcd     0xe1a06000
    dcd     0xe1590006
    dcd     0x0a000003
    dcd     0xe1a00008
    dcd     0xe046100a
    bl      func_ov012_0205b584
    dcd     0xe1a09006
    dcd     0xe5d51be0
    dcd     0xe3510000
    dcd     0x1a000009
    dcd     0xe1d700b0
    dcd     0xe2000902
    dcd     0xe1b007c0
    dcd     0x0a000005
    bl      func_02005630
    dcd     0xe3a00000
    bl      func_0200d49c
    dcd     0xe3a00001
    dcd     0xe5c50be0
    dcd     0xea000010
    dcd     0xe3510000
    dcd     0x0a00000e
    dcd     0xe1d700b0
    dcd     0xe2000902
    dcd     0xe1b007c0
    dcd     0x1a00000a
    dcd     0xe3a00001
    bl      func_0200d49c
    dcd     0xe3500000
    dcd     0x0a000006
    dcd     0xe3a00000
    dcd     0xe5c50be0
    bl      func_0201e428
    bl      func_0201e374
    bl      func_0201e438
    bl      func_0201e3cc
    bl      func_0200566c
    bl      func_ov024_02084db8
    dcd     0xe3500000
    dcd     0x0affffab
    dcd     0xe1d800b2
    dcd     0xe3100004
    dcd     0x0a00000b
    bl      func_ov012_0205b280
    dcd     0xe3500000
    dcd     0x1a000003
    bl      OS_WaitVBlankIntr
    bl      func_ov012_0205b280
    dcd     0xe3500000
    dcd     0x0afffffb
    dcd     0xe1d800b2
    dcd     0xe3100001
    dcd     0x0a000001
    dcd     0xe2880004
    bl      func_02021048
    bl      func_ov024_02084b14
    dcd     0xe3a01003
    dcd     0xe2880902
    dcd     0xe5801bdc
    dcd     0xe5801bd8
    dcd     0xe1d800b2
    dcd     0xe3100001
    dcd     0x0a00000a
    dcd     0xea000003
    dcd     0xe2880004
    bl      func_02020e58
    dcd     0xe3500000
    dcd     0x0a000005
    dcd     0xe3e0000f
    bl      func_0201e374
    dcd     0xe3e0000f
    bl      func_0201e3cc
    dcd     0xe3a00000
    dcd     0xe8bd8ff8
    dcd     0xe2880004
    bl      func_02020cc8
    dcd     0xe3a00000
    bl      func_02031574
    dcd     0xe3a00000
    bl      func_02030e64
    dcd     0xe5980130
    dcd     0xe3500000
    dcd     0x0a000003
    dcd     0xe3500001
    dcd     0x0a000003
    dcd     0xe3500002
    dcd     0x1a000001
    dcd     0xe3a00002
    dcd     0xe1c800b0
    dcd     0xe3e0000f
    bl      func_0201e374
    dcd     0xe3e0000f
    bl      func_0201e3cc
    dcd     0xe59f000c
    dcd     0xe8bd8ff8
    dcd     0x04000130
    dcd     0x027fffa8
    dcd     0x00002fff
    dcd     func_ov012_0205b8ac
}
