struct v5 { int w[5]; };
struct v3 { int a, b, c; };
struct slot { void *ptr; int pad; };

extern struct v5 data_ov133_020d49b8;
extern struct v3 data_02041dc8;
extern unsigned short data_ov133_020d4a4c[];
extern unsigned short data_ov133_020d4a58[];
extern int data_ov133_020d4a64;

extern void func_ov133_020d1c74(void), func_ov133_020d1cbc(void), func_ov133_020d1ce0(void);
extern void func_ov133_020d1d54(void), func_ov133_020d22a0(void), func_ov133_020d1ed8(void);
extern void func_ov133_020d22fc(void), func_ov133_020d25b0(void), func_ov133_020d1ea8(void);

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern void *func_0203bee8();
extern void *func_ov107_020c9e50();
extern void *func_0203d15c();
extern void func_ov107_020c9074();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern long long func_ov107_020c319c();
extern void func_0203355c();

void func_ov133_020d1a24(int param_1) {
    struct v5 tbl;
    struct { struct v3 t; int scale; } g;
    int i;
    long long r;
    tbl = data_ov133_020d49b8;
    *(void **)(param_1 + 8) = func_ov133_020d1c74;
    *(void **)(param_1 + 0xc) = func_ov133_020d1cbc;
    *(void **)(param_1 + 0x10) = func_ov133_020d1ce0;
    *(void **)(param_1 + 0x1c) = func_ov133_020d1d54;
    *(void **)(param_1 + 0x30) = func_ov133_020d22a0;
    *(void **)(param_1 + 0x34) = func_ov133_020d1ed8;
    *(void **)(param_1 + 0x1d0) = func_ov133_020d22fc;
    *(void **)(param_1 + 0x1e0) = func_ov133_020d25b0;
    *(void **)(param_1 + 0x1dc) = func_ov133_020d1ea8;
    *(int *)(param_1 + 0x70) = 0x800;
    *(int *)(param_1 + 0x64) = 0;
    *(int *)(param_1 + 0x68) = 0x800;
    *(int *)(param_1 + 0x6c) = 0;
    *(void **)(param_1 + 0x384) = func_0203b898(func_ov107_020c9440(param_1));
    func_0203bfb4(*(int *)(param_1 + 0x9c), *(void **)(param_1 + 0x384));
    *(void **)(param_1 + 0x390) = func_0203bee8(*(int *)(param_1 + 0x384), 1, data_ov133_020d4a4c);
    *(void **)(param_1 + 0x3c0) = func_0203bee8(*(int *)(param_1 + 0x384), 1, data_ov133_020d4a58);
    *(void **)(param_1 + 0x3c8) = func_ov107_020c9e50(func_ov107_020c9440(param_1, 1), &data_ov133_020d4a64);
    *(void **)(param_1 + 0x3c4) = func_0203d15c(0x28);
    for (i = 0; i < 5; i++) {
        ((struct slot *)*(int *)(param_1 + 0x3c4))[i].ptr = func_0203b898(func_ov107_020c9440(param_1, tbl.w[i]));
        func_ov107_020c9074(param_1, ((struct slot *)*(int *)(param_1 + 0x3c4))[i].ptr);
        *(int *)((char *)((struct slot *)*(int *)(param_1 + 0x3c4))[i].ptr + 0x5c) |= 2;
    }
    func_ov107_020c92b0(param_1, 0, 1, 0, 0x1000);
    func_ov107_020c92b0(param_1, 1, 1, 0, 0x1000);
    func_ov107_020c92b0(param_1, 2, 1, 0, 0x1000);
    func_ov107_020c92b0(param_1, 4, 1, 0, 0x1000);
    g.t = data_02041dc8;
    g.scale = 0x800;
    *(void **)(param_1 + 0x388) = func_01fffca8(param_1 + 0x22c, 0x10, 100);
    **(int **)(param_1 + 0x388) = (int)func_ov107_020c319c(&g);
    {
        int *p = func_01fffca8(param_1 + 0x144, 4, 100);
        r = func_ov107_020c319c(&g);
        *p = (int)r;
        *(int *)(param_1 + 0x38c) = (int)r;
    }
    func_0203355c(0x119, (int)((unsigned long long)r >> 32));
}
