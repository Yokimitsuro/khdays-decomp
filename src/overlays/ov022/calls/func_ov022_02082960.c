typedef unsigned short u16;
typedef unsigned int u32;

extern void GX_SetBankForTex(int bank);
extern void GX_BeginLoadOBJExtPltt(int offset);
extern void func_02010f08(void);
extern void func_02010e80(int mode, int enable);
extern void func_02011134(void *matrixState);
extern void func_0201133c(void);
extern void func_02011174(int value, int installCallbacks);
extern void func_ov002_02076028(int top);
extern void G3X_SetClearColor(int red, int green, int blue, int alpha, int polygonId);
extern void func_ov002_02078ef8(void);

static volatile u16 *const REG_DISP3DCNT = (volatile u16 *)0x04000060;

void func_ov022_02082960(void)
{
    u32 mask;
    u32 matrixState[10];

    GX_SetBankForTex(0xf);
    GX_BeginLoadOBJExtPltt(0x60);

    mask = 0xffffcffd;
    *REG_DISP3DCNT = *REG_DISP3DCNT & mask;
    *REG_DISP3DCNT = *REG_DISP3DCNT & 0xcffb;
    *REG_DISP3DCNT = (*REG_DISP3DCNT & ~0x3000) | 8;

    func_02010f08();
    func_02010e80(4, 1);

    matrixState[0] = 0;
    matrixState[1] = 0x20000;
    matrixState[2] = 0;
    matrixState[3] = 0x20000;
    matrixState[4] = 0;
    matrixState[5] = 0;
    matrixState[6] = 0;
    matrixState[7] = 0x20000;
    matrixState[8] = 0;
    matrixState[9] = 0x20000;
    func_02011134(matrixState);
    func_0201133c();
    func_02011174(0x8000, 1);
    func_ov002_02076028(1);
    G3X_SetClearColor(0, 0x1f, 0x7fff, 0x3f, 0);
    func_ov002_02078ef8();
}
