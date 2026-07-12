/* ov301 enemy-actor init (408B). Sets state callbacks + fields, block-inits the
 * param+0x1fc telemetry struct and a local descriptor, registers two list slots. */
extern int func_ov301_020cc15c, func_ov301_020cc178, func_ov301_020cc240;
extern int func_ov301_020cc1d8, func_ov301_020cc1e4, func_ov301_020cc28c, func_ov301_020cc1f0;
extern int data_02041dc8[], data_02042264[];
extern int  func_020c9440(int p, int a);
extern int  func_0203b898(int r0);
extern void func_0203bfb4(int a, int b, unsigned int c);
extern int *func_01fffca8(int p, int sz, int n);
extern int  func_020c3210(void *p);
extern int  func_020c319c(int p);

struct blk6 { int a, b, c, d, e, f; };
struct blk3 { int x, y, z; };

void func_ov301_020cbfc4(int param_1, int param_2, int param_3, int param_4) {
    int iVar1 = 0xfffff116;
    unsigned int uVar4 = 0xfffff7a8;
    struct { int v[8]; } b;
    struct blk6 s;
    int *slot;

    *(int *)(param_1 + 8)     = (int)&func_ov301_020cc15c;
    *(int *)(param_1 + 0xc)   = (int)&func_ov301_020cc178;
    *(int *)(param_1 + 0x30)  = (int)&func_ov301_020cc240;
    *(int *)(param_1 + 0x28)  = (int)&func_ov301_020cc1d8;
    *(int *)(param_1 + 0x2c)  = (int)&func_ov301_020cc1e4;
    *(int *)(param_1 + 0x1d0) = (int)&func_ov301_020cc28c;
    *(int *)(param_1 + 0x1dc) = (int)&func_ov301_020cc1f0;
    *(char *)(param_1 + 0x1c9) = 2;
    *(int *)(param_1 + 0x70) = 0x1900;
    *(int *)(param_1 + 0x64) = 0;
    *(int *)(param_1 + 0x68) = 0x400;
    *(int *)(param_1 + 0x6c) = 0;

    s.a = iVar1;
    s.b = 0x17;
    s.c = uVar4;
    s.d = iVar1 + 0x1dd3;
    s.e = 0x1c3e;
    s.f = uVar4 + 0xd64;
    *(struct blk6 *)(param_1 + 0x1fc) = s;

    func_020c9440(param_1, 0);
    *(int *)(param_1 + 0x384) = func_0203b898(param_1);
    func_0203bfb4(*(int *)(param_1 + 0x9c), *(int *)(param_1 + 0x384), uVar4);

    *(unsigned short *)(param_1 + 0x1ae) |= 0x10;
    *(struct blk3 *)&b.v[0] = *(struct blk3 *)data_02041dc8;
    *(struct blk3 *)&b.v[3] = *(struct blk3 *)data_02042264;
    b.v[6] = 0x4000;
    b.v[7] = 0x1900;

    *(int *)(param_1 + 0x388) = (int)func_01fffca8(param_1 + 0x22c, 0x10, 0x64);
    **(int **)(param_1 + 0x388) = func_020c3210(&b);

    slot = func_01fffca8(param_1 + 0x144, 4, 0x64);
    *slot = func_020c319c(param_1 + 0x64);
    *(int *)(param_1 + 0x38c) = *slot;
}
