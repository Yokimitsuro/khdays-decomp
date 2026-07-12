/* ov296 twin of func_ov295_020d3844. ov295 and ov296 are byte-identical
 * overlays; this is the same NONMATCHING C with the shared relative
 * offsets and every ov295-internal address rebased +0x1e20. */
/* ov295 (byte-identical with ov296) — enemy-actor init (348B). Installs state
 * callbacks + spawn fields, creates a subitem, seeds two sorted list slots from a
 * shared descriptor, and kicks the intro. */
extern int data_020d57c0, data_020d57dc, data_020d5840;
extern void func_ov296_020d588c(void);
extern int data_02041dc8[];
extern int  func_020c9440(int p);
extern int  func_0203b898(int r0);
extern void func_0203bfb4(int a, int b);
extern void func_0203ca14(int a, int b, int c, int d);
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_020c92b0(int a, int b, int c, int d, int e);
extern int *func_01fffca8(int p, int sz, int n);
extern int  func_020c319c(void *p);
extern void func_0203355c(short a, int b);

struct blk3 { int x, y, z; };

void func_ov296_020d5664(int param_1) {
    int desc[4];
    int *slot, r;

    *(int *)(param_1 + 8)     = (int)&data_020d57c0;
    *(int *)(param_1 + 0xc)   = (int)&data_020d57dc;
    *(int *)(param_1 + 0x30)  = (int)&data_020d5840;
    *(int *)(param_1 + 0x1d0) = (int)&func_ov296_020d588c;
    *(char *)(param_1 + 0x1c9) = 2;
    *(int *)(param_1 + 0x70) = 0x1200;
    *(int *)(param_1 + 0x64) = 0;
    *(int *)(param_1 + 0x68) = 0;
    *(int *)(param_1 + 0x6c) = 0;
    *(unsigned short *)(param_1 + 0x1ae) |= 0x10;

    *(int *)(param_1 + 0x384) = func_0203b898(func_020c9440(param_1));
    func_0203bfb4(*(int *)(param_1 + 0x9c), *(int *)(param_1 + 0x384));
    func_0203ca14(*(int *)(param_1 + 0x384) + 4, 0, -0x1200, 0);
    func_0203b9fc(*(int *)(param_1 + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(param_1 + 0x384), 4, 0, 1);
    func_020c92b0(param_1, 2, 2, 0, 0x2000);

    *(struct blk3 *)desc = *(struct blk3 *)data_02041dc8;
    desc[3] = 0x1200;

    *(int *)(param_1 + 0x388) = (int)func_01fffca8(param_1 + 0x22c, 0x10, 0x64);
    **(int **)(param_1 + 0x388) = func_020c319c(desc);

    slot = func_01fffca8(param_1 + 0x144, 4, 0x64);
    r = func_020c319c(desc);
    *slot = r;
    *(int *)(param_1 + 0x390) = r;
    func_0203355c(0x171, r);
}
