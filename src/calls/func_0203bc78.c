typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int fx32;

typedef struct Quat { fx32 w, x, y, z; } Quat;
typedef struct VecFx32 { fx32 x, y, z; } VecFx32;
typedef struct MtxFx33 { fx32 m[3][3]; } MtxFx33;
typedef struct MtxFx43 { fx32 m[4][3]; } MtxFx43;
typedef struct MtxFx44 { fx32 m[4][4]; } MtxFx44;

typedef struct Flags5c {
    int bit0 : 1;
    int bit1 : 1;
    int skipRender : 1;
} Flags5c;

typedef struct RenderCtx {
    u16 flags;                  /* +0x00 */
    char pad02[0x1e];
    u32 objFlags;                /* +0x20 */
    char pad24[0x104 - 0x24];
    u16 field104;                 /* +0x104 */
} RenderCtx;

typedef struct Node { int field0; struct Node *next; } Node;

typedef struct ObjList {
    int field0;
    Node *head;
    int pad8;
    int padc;
    Node listhead;
    int pad18, pad1c, pad20;
    Node *cur;
} ObjList;

typedef struct ObjNode {
    u16 flags;    /* +0x00 */
    u16 nodeID;   /* +0x02 */
    /* +0x04: transform block, accessed opaquely below */
} ObjNode;

typedef struct Self {
    char pad00[0x30];
    Quat quat;              /* +0x30 */
    VecFx32 vecA;            /* +0x40 */
    VecFx32 position;        /* +0x4c */
    char pad58[0x5c - 0x58];
    Flags5c flags5c;         /* +0x5c */
    char pad60[0x70 - 0x60];
    u16 field70;              /* +0x70 */
    char pad72[0x88 - 0x72];
    RenderCtx *renderCtx;    /* +0x88 */
    char pad8c[0x90 - 0x8c];
    ObjList *objList;        /* +0x90 */
} Self;

typedef struct NNSG3dGlb {
    u32 cmd0;
    u32 mtxmode_proj;
    MtxFx44 projMtx;
    u32 mtxmode_posvec;
    MtxFx43 cameraMtx;
    u32 cmd1;
    u8 pad80_d4[0x54];
    u32 flag;
} NNSG3dGlb;

extern VecFx32 data_02047458;
extern MtxFx33 data_02047428;
extern VecFx32 data_0204744c;
extern NNSG3dGlb data_02047394;

extern void func_0202ec2c(MtxFx33 *mtx, const Quat *q);
extern void func_0202afdc(u16 *p, u16 v);
extern void func_01ffcec0(int value);
extern void func_0201574c(void);
extern void func_020279e0(u32 *param_1);
extern void *func_01fffd70(ObjList *o);
extern void *func_01fffd8c(ObjList *o);
extern int func_02016320(void *pRenderObj, MtxFx43 *pos, MtxFx33 *nrm, u32 nodeID);
extern void func_0203c960(void *o);
extern void func_0203ca30(void *dst, void *src);
extern void func_0203c9ec(unsigned char *ptr, void *nrm);

void func_0203bc78(Self *self, int region)
{
    MtxFx43 pos;
    MtxFx33 nrm;
    ObjNode *node;

    if (region != 0) {
        self->renderCtx->objFlags |= 4;
    }

    data_02047458 = self->position;
    func_0202ec2c(&data_02047428, &self->quat);
    data_0204744c = self->vecA;
    data_02047394.flag &= ~0xa4;

    if (self->renderCtx->flags & 0x40) {
        if (!self->flags5c.skipRender) {
            if (self->field70 == 0) {
                if (self->renderCtx->field104 == 0) {
                    func_0202afdc((u16 *)self->renderCtx, 0x7fff);
                }
            } else {
                func_0202afdc((u16 *)self->renderCtx, self->field70);
            }
            func_01ffcec0(self->renderCtx->field104);
        }
    }
    func_0201574c();
    func_020279e0(&self->renderCtx->objFlags);

    if (self->objList != 0) {
        node = (ObjNode *)func_01fffd70(self->objList);
        while (node != 0) {
            if (func_02016320(&self->renderCtx->objFlags, &pos, &nrm, node->nodeID)) {
                func_0203c960((char *)node + 4);
                if (node->flags & 1) {
                    func_0203ca30((char *)node + 4, &pos.m[3]);
                }
                if (node->flags & 2) {
                    func_0203c9ec((unsigned char *)node + 4, &nrm);
                }
            }
            node = (ObjNode *)func_01fffd8c(self->objList);
        }
    }

    self->renderCtx->objFlags &= ~4;
}
