/* Class initialiser: installs the actor's handler table, seeds its two motion
   pairs, builds the render object, opens four subitem channels and links two
   sorted list entries built from the seeded block at +0x64. */

extern void func_ov285_020d1b64(void), func_ov285_020d1b80(void);
extern void func_ov285_020d1bfc(void), func_ov285_020d1c48(void);
extern void func_ov285_020d1cbc(void), func_ov285_020d1bdc(void);

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern long long func_ov107_020c319c();

void func_ov285_020d1a24(int param_1)
{
    *(void **)(param_1 + 8) = func_ov285_020d1b64;
    *(void **)(param_1 + 0xc) = func_ov285_020d1b80;
    *(void **)(param_1 + 0x30) = func_ov285_020d1bfc;
    *(void **)(param_1 + 0x1d0) = func_ov285_020d1c48;
    *(void **)(param_1 + 0x1e0) = func_ov285_020d1cbc;
    *(void **)(param_1 + 0x1dc) = func_ov285_020d1bdc;
    *(int *)(param_1 + 0x70) = 0xc00;
    *(int *)(param_1 + 0x64) = 0;
    *(int *)(param_1 + 0x68) = 0xc00;
    *(int *)(param_1 + 0x6c) = 0;
    *(void **)(param_1 + 0x384) = func_0203b898(func_ov107_020c9440(param_1));
    func_0203bfb4(*(int *)(param_1 + 0x9c), *(void **)(param_1 + 0x384));
    func_ov107_020c92b0(param_1, 0, 1, 0, 0x1f33);
    func_ov107_020c92b0(param_1, 1, 1, 0, 0x1f33);
    func_ov107_020c92b0(param_1, 2, 1, 0, 0x1f33);
    func_ov107_020c92b0(param_1, 4, 1, 0, 0x1f33);
    *(void **)(param_1 + 0x38c) = func_01fffca8(param_1 + 0x22c, 0x10, 100);
    **(int **)(param_1 + 0x38c) = (int)func_ov107_020c319c(param_1 + 0x64);
    {
        int *p = func_01fffca8(param_1 + 0x144, 4, 100);
        int r = (int)func_ov107_020c319c(param_1 + 0x64);
        *p = r;
        *(int *)(param_1 + 0x388) = r;
    }
}
