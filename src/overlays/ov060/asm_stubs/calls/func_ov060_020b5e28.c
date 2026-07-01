extern void func_0202aee0(void);
extern void func_ov002_020521e4(void);
extern void func_ov022_020ad588(void);

asm void func_ov060_020b5e28(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe5940020
    dcd     0xe3a01000
    dcd     0xe2800004
    bl      func_0202aee0
    dcd     0xe2841c2a
    dcd     0xe284cec3
    dcd     0xe1d12bfa
    dcd     0xe2841fc3
    dcd     0xe1a03000
    dcd     0xe2810b03
    dcd     0xe28c1a02
    bl      func_ov002_020521e4
    dcd     0xe1a00004
    bl      func_ov022_020ad588
    dcd     0xe8bd8010
}
