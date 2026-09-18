struct v5 { int w[3]; };
struct v3 { int a, b, c; };
struct slot { void *ptr; int pad; };

extern struct v5 data_ov136_020d39d8;
extern struct v3 data_02041dc8;
extern unsigned short data_ov136_020d3a58[];
extern unsigned short data_ov136_020d3a60[];
extern unsigned short data_ov136_020d3a64[];

extern void func_ov136_020d1c88(void), func_ov136_020d1cd0(void), func_ov136_020d1d24(void);
extern void func_ov136_020d1fa4(void), func_ov136_020d1ea8(void), func_ov136_020d2000(void);
extern void func_ov136_020d2258(void), func_ov136_020d1cf4(void);
extern unsigned short data_ov136_020d3a4c[];

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

void func_ov136_020d1a24(int param_1) {
    struct v5 tbl;
    struct { struct v3 t; int scale; } g;
    int i;
    tbl = data_ov136_020d39d8;
    *(void **)(param_1 + 8) = func_ov136_020d1c88;
    *(void **)(param_1 + 0xc) = func_ov136_020d1cd0;
    *(void **)(param_1 + 0x1c) = func_ov136_020d1d24;
    *(void **)(param_1 + 0x30) = func_ov136_020d1fa4;
    *(void **)(param_1 + 0x34) = func_ov136_020d1ea8;
    *(void **)(param_1 + 0x1d0) = func_ov136_020d2000;
    *(void **)(param_1 + 0x1e0) = func_ov136_020d2258;
    *(void **)(param_1 + 0x1dc) = func_ov136_020d1cf4;
    *(int *)(param_1 + 0x70) = 0x800;
    *(int *)(param_1 + 0x64) = 0;
    *(int *)(param_1 + 0x68) = 0x800;
    *(int *)(param_1 + 0x6c) = 0;
    *(void **)(param_1 + 0x384) = func_0203b898(func_ov107_020c9440(param_1));
    func_0203bfb4(*(int *)(param_1 + 0x9c), *(void **)(param_1 + 0x384));
    *(void **)(param_1 + 0x394) = func_0203bee8(*(int *)(param_1 + 0x384), 1, data_ov136_020d3a4c);
    *(void **)(param_1 + 0x3a0) = func_ov107_020c9e50(func_ov107_020c9440(param_1, 1), &data_ov136_020d3a58);
    *(void **)(param_1 + 0x3a4) = func_0203d15c(0x18);
    for (i = 0; i < 3; i++) {
        ((struct slot *)*(int *)(param_1 + 0x3a4))[i].ptr = func_0203b898(func_ov107_020c9440(param_1, tbl.w[i]));
        func_ov107_020c9074(param_1, ((struct slot *)*(int *)(param_1 + 0x3a4))[i].ptr);
        *(int *)((char *)((struct slot *)*(int *)(param_1 + 0x3a4))[i].ptr + 0x5c) |= 2;
    }
    func_ov107_020c92b0(param_1, 0, 1, 0, 0x1333);
    func_ov107_020c92b0(param_1, 1, 1, 0, 0x1333);
    func_ov107_020c92b0(param_1, 2, 1, 0, 0x1333);
    func_ov107_020c92b0(param_1, 4, 1, 0, 0x1333);
    *(void **)(param_1 + 0x398) = func_0203bee8((int)((struct slot *)*(int *)(param_1 + 0x3a4))[0].ptr, 1, data_ov136_020d3a60);
    *(void **)(param_1 + 0x39c) = func_0203bee8((int)((struct slot *)*(int *)(param_1 + 0x3a4))[0].ptr, 1, data_ov136_020d3a64);
    g.t = data_02041dc8;
    g.scale = 0x99a;
    *(void **)(param_1 + 0x38c) = func_01fffca8(param_1 + 0x22c, 0x10, 100);
    **(int **)(param_1 + 0x38c) = (int)func_ov107_020c319c(&g);
    {
        int *p = func_01fffca8(param_1 + 0x144, 4, 100);
        *(int *)(param_1 + 0x390) = *p = (int)func_ov107_020c319c(&g);
    }
    func_0203355c(0x11c);
}
