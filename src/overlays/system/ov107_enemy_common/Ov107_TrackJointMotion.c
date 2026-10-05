/* Follows the bound joint's position, updating the node's previous position and motion delta. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { fx32 rot[9]; VecFx32 pos; } MtxFx43;

extern void Obj_RenderModel(void *self, int region);
extern int NNS_G3dGetResultMtx(void *pRenderObj, MtxFx43 *pos, void *nrm, u32 nodeID);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Normalize(const VecFx32 *source, VecFx32 *destination);
extern void ScaleVec3Fx12(int factor, VecFx32 *src, VecFx32 *dst);
extern unsigned char gObjSystem;

typedef struct {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char rest : 4;
} Flags4;

typedef struct {
    short id;             /* +0 */
    short field_02;        /* +2 */
    union {
        unsigned char field_04; /* +4 */
        Flags4 flags04;
    };
    unsigned char pad05[3];
    VecFx32 f08;             /* +8 */
    VecFx32 f14;               /* +0x14 */
    VecFx32 f20;                 /* +0x20 */
    VecFx32 f2c;                   /* +0x2c */
    unsigned char pad38[0x38 - 0x38];
    int f38;                         /* +0x38 */
} Node;

void Ov107_TrackJointMotion(char *self, int region)
{
    Node *node = *(Node **)(self + 0x84);

    Obj_RenderModel(self, region);

    if (((unsigned)(node->field_04 << 0x1c)) >> 0x1f) {
        node->f38 = 0;
        node->f08 = node->f20;
        node->field_04 = (unsigned char)(node->field_04 & ~8);
    }

    {
        MtxFx43 mtx;
        void *renderObj = (char *)*(void **)(self + 0x88) + 0x20;

        if (NNS_G3dGetResultMtx(renderObj, &mtx, 0, (u16)node->id) != 0) {
            VecFx32 tmpPos = mtx.pos;

            if (node->flags04.bit0) {
                node->field_04 = (unsigned char)(node->field_04 & ~1);
                node->f20 = tmpPos;
                node->f08 = node->f20;
                node->f38 = 0;
                return;
            }

            VEC_Subtract(&tmpPos, &node->f08, &node->f2c);
            node->f38 = VEC_Normalize(&node->f2c, &node->f14);

            if (gObjSystem == 1) {
                node->f38 = (int)(((long long)node->f38 * 0xaaa + 0x800) >> 12);
                ScaleVec3Fx12(node->f38, &node->f14, &node->f2c);
            } else if (LoadGlobalU16At0() != 0x2a) {
                if (gObjSystem == 2) {
                    node->f38 = node->f38 * 2;
                    ScaleVec3Fx12(node->f38, &node->f14, &node->f2c);
                }
            }

            node->f08 = tmpPos;
        }
    }

    if (*(unsigned char *)(self + 0xad) != 0) {
        return;
    }

    if (node->flags04.bit2) {
        SetSubitemState(self, 0, node->field_02, 0);
        node->field_04 = (unsigned char)(node->field_04 | 8);
        return;
    }

    node->field_04 = (unsigned char)(node->field_04 | 2);
}
