/*
 * Camera_CommitMatricesEx - variant of Camera_CommitMatrices that takes the projection inputs as
 * explicit arguments. Builds the projection matrix via func_02004eac (params param_2..param_5 plus
 * the actor's near/far words at +0xc/+0x10, FX32_ONE scale, into data_0204739c), clears GX dirty
 * bits 0x50, caches the actor's eye/up/target vectors (+0x20/+0x2c/+0x14) into the global camera
 * state (data_020475ac/b8/c4), builds the view matrix via MTX_LookAt into data_020473e0, and clears
 * GX dirty bits 0xe8.
 *
 * ARM. Same GX-block-as-struct (data_02047394, flags at +0xd4) and VecFx32 struct-copy modeling as
 * Camera_CommitMatrices. The global pool order is fixed by first reference: the projection output
 * (data_0204739c) comes first and the view output (data_020473e0) last.
 */

typedef struct { int x, y, z; } VecFx32;

/* Camera actor: near/far words then the look-at points. */
typedef struct {
    char    _0[0xc];
    int     fC;             /* +0xc: near */
    int     f10;            /* +0x10: far */
    VecFx32 target;         /* +0x14 */
    VecFx32 pos;            /* +0x20 */
    VecFx32 up;             /* +0x2c */
} CamActor;

extern struct { char _p00[0xd4]; int flags; } data_02047394;   /* GX dirty flags at +0xd4 */
extern char    data_0204739c[];   /* projection matrix output */
extern VecFx32 data_020475ac;     /* cached eye */
extern VecFx32 data_020475b8;     /* cached up */
extern VecFx32 data_020475c4;     /* cached target */
extern char    data_020473e0[];   /* view (look-at) matrix output */

extern void func_02004eac(int a, int b, int c, int d, int e, int f, int scale, void *projOut);
extern void func_01ff9c04(const VecFx32 *pos, const VecFx32 *up, const VecFx32 *target, void *viewOut);

void func_02023d70(CamActor *param_1, int param_2, int param_3, int param_4, int param_5)
{
    func_02004eac(param_2, param_3, param_4, param_5, param_1->fC, param_1->f10, 0x1000, data_0204739c);
    data_02047394.flags &= ~0x50;
    data_020475ac = param_1->pos;
    data_020475b8 = param_1->up;
    data_020475c4 = param_1->target;
    func_01ff9c04(&param_1->pos, &param_1->up, &param_1->target, data_020473e0);
    data_02047394.flags &= ~0xe8;
}
