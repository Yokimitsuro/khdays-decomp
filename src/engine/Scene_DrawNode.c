/* Walks one node of the scene graph. A node that carries a display list uploads its matrix straight
 * to the geometry engine. Otherwise the node publishes its position, rebuilds its matrix from its
 * own yaw and pitch when the rebuild bit is set, hands the matrix to the camera and clears two of
 * the camera's flags. It then recurses: with the recurse bit set and a child present it either runs
 * the node's own callback or walks the children in turn, giving each its joint matrix. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct MtxFx43 {
    s32 m[12];
} MtxFx43;

typedef struct SceneNode SceneNode;

struct SceneNode {
    u16 flags;
    char _002[0x1e];
    char object[0x5c];
    u16 angleY;
    u16 angleX;
    MtxFx43 matrix;
    VecFx32 position;
    void *displayList;
    SceneNode *child;
    SceneNode *next;
    s16 jointId;
};

typedef struct CameraState {
    char _000[0xd4];
    unsigned int flags;
} CameraState;

extern void GX_SendFifoWords(unsigned int command, const void *src,
                          unsigned int words);
extern void MTX_RotY33_(MtxFx43 *matrix, s32 sine, s32 cosine);
extern void NNS_G3dGlbFlush(void);
extern void NNS_G3dRenderObjSetCallBack(void *object, void (*callback)(void), int unused,
                          int field24, int field25);
extern void NNS_G3dRenderObjResetCallBack(void *object);
extern void MaterialColorScale_SetRgb555(int value);
extern int NNS_G3dGetResultMtx(void *object, MtxFx43 *matrix, void *unused,
                         int jointId);
extern void SceneNode_JointCallback(void);

extern VecFx32 data_02047458;
extern const s16 data_0203d210[];
extern MtxFx43 data_02047428;
extern CameraState NNS_G3dGlb;
extern SceneNode *data_0204c1f4;

void Scene_DrawNode(SceneNode *node)
{
    SceneNode *child;

    if (node->displayList != 0) {
        GX_SendFifoWords(0x17, &node->matrix, 0xc);
    } else {
        data_02047458 = node->position;
        if (node->flags & 0x20) {
            int index = (node->angleY >> 4) * 2;
            MTX_RotY33_(&node->matrix, data_0203d210[index],
                        data_0203d210[index + 1]);

            if (node->angleX != 0) {
                s32 sine;
                s32 cosine;
                s32 value;

                index = (node->angleX >> 4) * 2;
                cosine = data_0203d210[index + 1];
                sine = data_0203d210[index];
                node->matrix.m[4] = cosine;
                node->matrix.m[1] = sine;
                value = node->matrix.m[0];
                node->matrix.m[3] = (s32)(((s64)-sine * value) >> 12);
                node->matrix.m[0] = (s32)(((s64)cosine * value) >> 12);
                value = node->matrix.m[2];
                node->matrix.m[5] = (s32)(((s64)-sine * value) >> 12);
                node->matrix.m[2] = (s32)(((s64)cosine * value) >> 12);
            }
            node->flags &= ~0x20;
        }

        data_02047428 = node->matrix;
        NNS_G3dGlb.flags &= ~0xa4;
        NNS_G3dGlbFlush();
    }

    if ((node->flags & 0x10) && node->child != 0) {
        data_0204c1f4 = node;
        if (!(node->flags & 0x80)) {
            NNS_G3dRenderObjSetCallBack(node->object, SceneNode_JointCallback, 0, 6, 3);
        }
    }

    if (node->flags & 0x40) {
        MaterialColorScale_SetRgb555(*(u16 *)((char *)node + 0x104));
    }
    NNS_G3dDraw(node->object);

    child = node->child;
    if (child == 0)
        return;

    if ((node->flags & 0x10) && !(node->flags & 0x80)) {
        NNS_G3dRenderObjResetCallBack(node->object);
        return;
    }

    while (child != 0) {
        NNS_G3dGetResultMtx(node->object, &child->matrix, 0, child->jointId);
        if (child->flags & 8)
            Mtx33_ApplyFixedRotation(&child->matrix);
        child = child->next;
    }
}
