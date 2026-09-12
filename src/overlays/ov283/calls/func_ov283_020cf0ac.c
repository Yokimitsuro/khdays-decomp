typedef signed char s8;

typedef struct { int a, b, c, d; } T4;
typedef struct { T4 t; char pad[0x28 - 16]; unsigned char flag; } S;

typedef struct {
    void *f0;
    void *f1;
} Ctx;

typedef struct {
    void *field_00;
    Ctx *ctx;
} Self;

extern void func_ov107_020c5c54(char *node, void *pos);
extern int func_0203c9d0(S *dst, S *src);

void func_ov283_020cf0ac(Self *self) {
    Ctx *ctx = self->ctx;

    if (*(s8 *)((char *)ctx->f0 + 0x1c6) != 1) {
        return;
    }
    if (ctx->f1 == 0) {
        return;
    }

    func_ov107_020c5c54((char *)ctx->f0, (char *)ctx->f1 + 0x14);
    func_0203c9d0((S *)((char *)ctx->f0 + 0xa0), (S *)((char *)ctx->f1 + 4));
}
