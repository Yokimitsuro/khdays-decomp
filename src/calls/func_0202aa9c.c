typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef struct VecFx32 {
    s32 x, y, z;
} VecFx32;

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

extern void func_01ff9f00(unsigned int command, const void *src,
                          unsigned int words);
extern void MTX_RotY33_(MtxFx43 *matrix, s32 sine, s32 cosine);
extern void func_0201571c(void);
extern void func_02014e18(void *object, void (*callback)(void), int unused,
                          int field24, int field25);
extern void func_02014e2c(void *object);
extern void func_01ffcec0(int value);
extern void func_020279e0(void *object);
extern int func_02016320(void *object, MtxFx43 *matrix, void *unused,
                         int jointId);
extern void func_0202a984(MtxFx43 *matrix);
extern void func_0202a9d0(void);

extern VecFx32 data_02047458;
extern volatile s16 data_0203d210[];
extern MtxFx43 data_02047428;
extern CameraState data_02047394;
extern SceneNode *data_0204c1f4;

void func_0202aa9c(SceneNode *node)
{
    SceneNode *child;

    if (node->displayList != 0) {
        func_01ff9f00(0x17, &node->matrix, 0xc);
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
        data_02047394.flags &= ~0xa4;
        func_0201571c();
    }

    if ((node->flags & 0x10) && node->child != 0) {
        data_0204c1f4 = node;
        if (!(node->flags & 0x80)) {
            func_02014e18(node->object, func_0202a9d0, 0, 6, 3);
        }
    }

    if (node->flags & 0x40) {
        func_01ffcec0(*(u16 *)((char *)node + 0x104));
    }
    func_020279e0(node->object);

    child = node->child;
    if (child == 0)
        return;

    if ((node->flags & 0x10) && !(node->flags & 0x80)) {
        func_02014e2c(node->object);
        return;
    }

    while (child != 0) {
        func_02016320(node->object, &child->matrix, 0, child->jointId);
        if (child->flags & 8)
            func_0202a984(&child->matrix);
        child = child->next;
    }
}
