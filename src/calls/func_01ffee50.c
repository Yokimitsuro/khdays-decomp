typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct CollisionRegion {
    s32 centerX00;
    s32 centerZ04;
    s32 size08;
} CollisionRegion;

typedef struct CollCastState {
    u8 pad00[0x0c];
    void *modelData0c;
    u8 pad10[0x34 - 0x10];
    s32 bound34;
    s32 bound38;
    s32 bound3c;
    s32 bound40;
} CollCastState;

typedef struct CollisionTraversalFrame {
    s16 childIndex00;
    u16 nodeFlags02;
    CollisionRegion region04;
} CollisionTraversalFrame;

typedef struct CollisionModel {
    u8 pad00[0x80];
    u16 enabled80;
    u8 pad82[2];
    CollisionRegion region84;
    u8 pad90[0x9c - 0x90];
    u16 *root9c;
    u8 padA0[8];
    void *modelDataA8;
} CollisionModel;

typedef struct CollisionHitRecord {
    CollisionModel *model00;
    void *face04;
    u32 unknown08;
    s32 distance0c;
} CollisionHitRecord;

extern CollisionTraversalFrame data_027e06e4;
extern CollisionTraversalFrame *data_027e06e0;
extern CollisionHitRecord data_027e0764;

extern void func_01ffeba0(CollCastState *state, CollisionModel *model);
extern void *func_01ffe0f0(u16 *root, CollCastState *state);

int func_01ffee50(CollCastState *state, CollisionModel *model)
{
    int hit = 0;
    s32 size;
    int i;
    void *face;

    if (model->enabled80 == 0) {
        return 0;
    }

    state->modelData0c = model->modelDataA8;
    func_01ffeba0(state, model);
    size = model->region84.size08;

    if (state->bound34 - model->region84.centerX00 <= size &&
        state->bound38 - model->region84.centerZ04 <= size &&
        model->region84.centerX00 - state->bound3c <= size &&
        model->region84.centerZ04 - state->bound40 <= size) {
        CollisionTraversalFrame *frames = &data_027e06e4;
        s32 levelSize = size;

        for (i = 0; i < 8; i++) {
            frames[i].region04.size08 = levelSize;
            levelSize /= 2;
        }

        data_027e06e0 = frames;
        frames[0].region04 = model->region84;

        face = func_01ffe0f0(model->root9c, state);
        if (face != 0) {
            hit = 1;
            data_027e0764.model00 = model;
            data_027e0764.face04 = face;
        }
    }

    return hit;
}
