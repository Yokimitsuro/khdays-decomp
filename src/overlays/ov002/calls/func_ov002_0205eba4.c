typedef unsigned char u8;
typedef short s16;

typedef struct {
    u8 pad0000[0x69c];
    int nField069c;                 /* +0x69c */
    u8 pad06a0[0xc];
    int nRowY;                      /* +0x6ac */
    u8 pad06b0[0x20];
    int nOriginX;                   /* +0x6d0 */
    u8 pad06d4[0x108];
    int nCursor;                    /* +0x7dc */
} Ov002CursorCtx;

extern int data_ov002_0207f624;

extern int func_ov002_020536bc(int nTag);
extern void func_ov002_0205376c(int nNode, int nArg);
extern int func_ov002_02053558(int nTag);
extern void func_ov002_02053578(int nObj, int y, int x);
extern void func_ov002_020535a4(int nObj);
extern void func_ov002_02053720(int nNode, int y, int x);
extern void func_ov002_02053700(int nNode);
extern void func_ov002_020536dc(int nNode, int bArmed);

void func_ov002_0205eba4(int index) {
    Ov002CursorCtx *ctx = (Ov002CursorCtx *)data_ov002_0207f624;
int nNode;
    int nObj;
    s16 y;
    s16 x;

    nNode = func_ov002_020536bc(0xd);
    func_ov002_0205376c(nNode, ctx->nField069c);
    y = (s16)ctx->nRowY;
    x = (s16)(ctx->nOriginX + index * 2);
    nObj = func_ov002_02053558(0x86);

    if (index >= 0) {
        func_ov002_02053578(nObj, y, (s16)(ctx->nOriginX + ctx->nCursor * 2));
        func_ov002_020535a4(nObj);
        func_ov002_02053720(nNode, y, x);
        func_ov002_02053700(nNode);
    } else {
        func_ov002_020536dc(nNode, 0);
    }

    ctx->nCursor = index;
}
