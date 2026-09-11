typedef struct { int a, b, c; } Blk12;

typedef struct {
    int p0;
    char pad1[4];
    int f8;
    char pad2[4];
    Blk12 blk;
    char pad3[0x2c];
    int f48;
    char pad4[0x1c];
    int f68;
    int f6c;
    char pad5[4];
    int f74;
} Ctx;

typedef struct {
    int field_00;
    Ctx *ctx;
} Self;

extern int func_ov283_020cc92c(int, int, int, int);
extern int func_ov107_020c9264(int, int, int);
extern void func_0203c634(int *a, int i, int v);
extern Blk12 data_02041dc8;
extern void func_ov283_020cdbfc(void);

void func_ov283_020cdb88(Self *self) {
    Ctx *ctx = self->ctx;

    func_ov283_020cc92c(ctx->p0, 0x173, 7, ctx->f8);
    func_ov107_020c9264(ctx->p0, 9, 0);

    ctx->f68 = 0;
    ctx->f6c = 0;
    ctx->f48 = 0;
    ctx->blk = data_02041dc8;
    ctx->f74 = 0;

    func_0203c634((int *)self, *(signed char *)((char *)self + 0x20), (int)func_ov283_020cdbfc);
}
