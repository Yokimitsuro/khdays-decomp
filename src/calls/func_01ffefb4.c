typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned char u8;

typedef struct CollisionRegion {
    s32 centerX00;
    s32 centerZ04;
    s32 size08;
} CollisionRegion;

typedef struct CollCastState {
    u8 pad00[8];
    void *modelData08;
    u8 pad0c[0x34 - 0x0c];
    s32 bound34;
    s32 bound38;
    s32 bound3c;
    s32 bound40;
    u8 pad44[0x74 - 0x44];
    s32 radius74;
} CollCastState;

typedef struct CollisionTraversalFrame {
    s16 childIndex00;
    u16 nodeFlags02;
    CollisionRegion region04;
} CollisionTraversalFrame;

typedef struct CollisionModel {
    u8 pad00[0x84];
    CollisionRegion region84;
    u8 pad90[0x9c - 0x90];
    u16 *root9c;
    u8 padA0[4];
    void *modelDataA4;
} CollisionModel;

typedef struct CollisionCallbackObject CollisionCallbackObject;
typedef struct CollisionFace CollisionFace;

typedef struct CollisionCallbackVtable {
    u8 pad00[0x14];
    void (*callback14)(CollisionCallbackObject *object,
                       CollCastState *state,
                       CollisionFace *face);
} CollisionCallbackVtable;

struct CollisionCallbackObject {
    u8 pad00[0x1c];
    CollisionCallbackVtable *vtable1c;
};

typedef struct CollisionHitRecord {
    CollisionModel *model00;
    CollisionFace *face04;
    CollisionCallbackObject *object08;
    s32 distance0c;
} CollisionHitRecord;

extern CollisionTraversalFrame data_027e06e4;
extern CollisionTraversalFrame *data_027e06e0;
extern CollisionHitRecord data_027e0764;
extern CollisionFace data_027e0774;

extern void func_01ffeba0(CollCastState *state, CollisionModel *model);
extern CollisionFace *func_01ffe82c(u16 *root, CollCastState *state);

static inline void RecordSphereHit(CollisionModel *model,
                                   CollCastState *state,
                                   CollisionFace *face)
{
    data_027e0764.model00 = model;
    data_027e0764.face04 = face;
    if (face == &data_027e0774) {
        CollisionCallbackObject *object = data_027e0764.object08;
        object->vtable1c->callback14(object, state, face);
    }
}

int func_01ffefb4(CollCastState *state, CollisionModel *model)
{
    int hit = 0;
    s32 radius = state->radius74;
    s32 size;
    int i;
    CollisionFace *face;

    state->modelData08 = model->modelDataA4;
    func_01ffeba0(state, model);
    state->bound34 -= radius;
    state->bound38 -= radius;
    state->bound3c += radius;
    state->bound40 += radius;
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

        if ((face = func_01ffe82c(model->root9c, state)) != 0) {
            hit = 1;
            RecordSphereHit(model, state, face);
        }
    }

    return hit;
}
