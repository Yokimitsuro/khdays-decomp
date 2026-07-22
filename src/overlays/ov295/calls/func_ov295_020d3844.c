typedef signed int s32;
typedef unsigned short u16;
typedef unsigned char u8;

struct v3 {
    int a;
    int b;
    int c;
};

struct Work4 {
    struct v3 vec;
    int d;
};

struct Obj {
    char pad00[0x08];
    void (*fn08)(void);
    void (*fn0c)(void);
    char pad10[0x20];
    void (*fn30)(void);
    char pad34[0x30];
    int cam[4];
    char pad74[0x28];
    void *p9c;
    char padA0[0xA4];
    char pool144[0x6A];
    u16 flags1ae;
    char pad1B0[0x19];
    u8 state1c9;
    char pad1CA[0x06];
    void (*fn1d0)(void);
    char pad1D4[0x58];
    char pool22c[0x158];
    char *p384;
    int *p388;
    int pad38c;
    int p390;
};

extern struct v3 data_02041dc8;

extern void func_ov295_020d39a0(void);
extern void func_ov295_020d39bc(void);
extern void func_ov295_020d3a20(void);
extern void func_ov295_020d3a6c(void);

extern void *func_ov107_020c9440(struct Obj *, int);
extern char *func_0203b898(void *);
extern void func_0203bfb4(void *, void *);
extern void func_0203ca14(void *, int, int, int);
extern void func_0203b9fc(void *, int, int, int);
extern void func_ov107_020c92b0(struct Obj *, int, int, int, int);
extern int *func_01fffca8(void *, int, int);
extern int func_ov107_020c319c(void *);
extern void func_0203355c(int, int);

void func_ov295_020d3844(struct Obj *arg0)
{
    struct Work4 work;
    int *slot;
    int result;

    arg0->fn08 = func_ov295_020d39a0;
    arg0->fn0c = func_ov295_020d39bc;
    arg0->fn30 = func_ov295_020d3a20;
    arg0->fn1d0 = func_ov295_020d3a6c;

    arg0->state1c9 = 2;

    arg0->cam[3] = 0x1200;
    arg0->cam[0] = 0;
    arg0->cam[1] = 0;
    arg0->cam[2] = 0;

    arg0->flags1ae |= 0x10;

    arg0->p384 = func_0203b898(func_ov107_020c9440(arg0, 0));
    func_0203bfb4(arg0->p9c, arg0->p384);
    func_0203ca14(arg0->p384 + 4, 0, -0x1200, 0);
    func_0203b9fc(arg0->p384, 0, 0, 1);
    func_0203b9fc(arg0->p384, 4, 0, 1);
    func_ov107_020c92b0(arg0, 2, 2, 0, 0x2000);

    work.vec = data_02041dc8;
    work.d = 0x1200;

    arg0->p388 = func_01fffca8(arg0->pool22c, 0x10, 0x64);
    *arg0->p388 = func_ov107_020c319c(&work);

    slot = func_01fffca8(arg0->pool144, 4, 0x64);
    result = (*slot = func_ov107_020c319c(&work));
    arg0->p390 = result;

    func_0203355c(0x171, result);
}
