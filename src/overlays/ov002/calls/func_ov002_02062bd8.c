/* Scene entry: allocate nothing -- the object is the current root heap block --
 * zero its first 0x1e0 bytes, seed the two 0xffff cursor fields and the -1
 * selection, load the two animation resources, then bring up the sub display
 * darkened (G2x_SetBlendBrightness_ on 0x04001050 = the SUB engine's BLDY, plane
 * mask 0x2f, ev -16) and register the per-frame step at func_ov002_02062190.
 * Returns the next scene step.
 *
 * data_0204c240 bit 2 is the boot-mode gate the anti-tamper path also reads: only
 * when it is set does this scene build the dialog object at +0x04.
 *
 * `unsigned char` on data_0204c240 is load-bearing -- signed gives ldrsb and an
 * extra zero register, and the total size still comes out right because mwcc then
 * reuses that zero for the following argument. */
typedef struct {
    char pad00[4];
    void *pDialog;          /* +0x04 */
    int nUnk08;             /* +0x08 */
    char pad0c[0x4c];
    int tween[7];           /* +0x58 */
    void *pStepObject;      /* +0x74 */
    void *pAnimA;           /* +0x78 */
    void *pAnimB;           /* +0x7c */
    char pad80[4];
    unsigned short wCursorA; /* +0x84 */
    unsigned short wCursorB; /* +0x86 */
    char pad88[0x24];
    int nSelected;          /* +0xac */
    char padb0[0x104];
    int aSubCtx[1];          /* +0x1b4 */
} Ov002SceneContext;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, unsigned char value, unsigned int size);
extern void *func_02024ee8(const void *res, int a);
extern void func_ov002_0205280c(void *dst, const void *src);
extern int func_ov002_02053558(int id);
extern void func_ov002_020535a4(void);
extern void func_ov002_020623c4(void);
extern void func_ov002_020624d8(void);
extern void func_ov002_0206250c(void);
extern void func_02035f84(void *tween);
extern void G2x_SetBlendBrightness_(unsigned int reg, int planeMask, int ev);
extern void *func_02023930(const void *res, int a);
extern void *func_ov002_020538c0(void *fn);
extern void func_02024d68(void);
extern void func_ov002_02053864(int a);
extern void func_ov002_02062e04(int a, int b);
extern void func_ov002_02062190(void);
extern void func_ov002_02062d74(void);

extern char *data_ov002_0207f62c;
extern char data_ov002_0207ed20[];
extern char data_ov002_0207ed30[];
extern char data_ov002_0207ed44[];
extern char data_ov002_0207ee70[];
extern unsigned char data_0204c240;

void *func_ov002_02062bd8(void) {
    Ov002SceneContext *ctx = NNSi_FndGetCurrentRootHeap();

    (&data_ov002_0207f62c)[1] = (char *)ctx;
    MI_CpuFill8(ctx, 0, 0x1e0);
    ctx->wCursorA = 0xffff;
    ctx->wCursorB = 0xffff;
    ctx->nSelected = -1;
    ctx->nUnk08 = 0;
    ctx->pAnimA = func_02024ee8(data_ov002_0207ed20, 0xe);
    ctx->pAnimB = func_02024ee8(data_ov002_0207ed30, 0xe);
    func_ov002_0205280c(ctx->aSubCtx, data_ov002_0207ed44);
    func_ov002_02053558(0x3e8);
    func_ov002_020535a4();
    func_ov002_020623c4();
    func_ov002_020624d8();
    func_ov002_0206250c();
    func_02035f84(ctx->tween);
    G2x_SetBlendBrightness_(0x4001050, 0x2f, -0x10);
    if ((data_0204c240 & 4) != 0) {
        ctx->pDialog = func_02023930(data_ov002_0207ee70, 0);
    }
    ctx->pStepObject = func_ov002_020538c0((void *)&func_ov002_02062190);
    func_02024d68();
    func_ov002_02053864(0);
    func_ov002_02062e04(0, 0);
    return (void *)&func_ov002_02062d74;
}
