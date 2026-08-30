/* Single-path quadtree traversal for a vertical collision ray. */
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct CollisionFace88 CollisionFace88;
typedef struct CollCastState CollCastState;
typedef struct CollisionObject CollisionObject;

typedef struct CollisionObjectVtable {
    void *slot00;
    void *slot04;
    s32 (*test08)(CollisionObject *, CollCastState *);
    void *slot0c;
    void (*finish10)(CollisionObject *, CollCastState *, void *);
} CollisionObjectVtable;

struct CollisionObject {
    void *field00;
    CollisionObject *next04;
    u8 pad08[0x1c - 0x08];
    CollisionObjectVtable *vtable1c;
    u16 field20;
    u16 rejectMask22;
    u32 field24;
    u32 rejectId28;
};

typedef struct CollisionNode {
    u16 flags00;
    s16 firstFace02;
    u32 field04;
    CollisionObject *objects08;
    struct CollisionNode *parent0c;
    struct CollisionNode *children10[4];
} CollisionNode;

struct CollisionFace88 {
    s32 bounds00[4];
    u16 flags10;
    u16 vertexCount12;
    u8 rest14[0x88 - 0x14];
};

struct CollCastState {
    u32 flags00;
    CollisionFace88 *faces04;
    u8 pad08[0x34 - 0x08];
    s32 bound34;
    s32 bound38;
    s32 bound3c;
    s32 bound40;
    u8 pad44[0x84 - 0x44];
    u32 rejectId84;
    u16 rejectMask88;
};

typedef struct CollisionTraversalFrame {
    s16 childIndex00;
    u16 nodeFlags02;
    s32 centerX04;
    s32 centerZ08;
    s32 size0c;
} CollisionTraversalFrame;

typedef struct CollisionHitRecord {
    u32 pad00[2];
    CollisionObject *object08;
} CollisionHitRecord;

extern s32 func_01ffd824(CollisionFace88 *, CollCastState *);
extern u8 data_027e0774[];
extern CollisionHitRecord data_027e0764;
extern CollisionTraversalFrame *data_027e06e0;

void *func_01ffdb54(CollisionNode *node, CollCastState *query)
{
    void *hit = 0;
    CollisionFace88 *face;
    CollisionObject *object;
    /* Reused for the accepted object address, then the frame X coordinate. */
    u32 workValue;
    s32 frameSize;
    CollisionTraversalFrame *frame;
    u16 nodeFlags;
    u16 child;
    CollisionTraversalFrame *nextFrame;
    u16 faceFlags;
    u16 rejectMask;
    s32 rejectId;
    s32 quarter;
    for (;;) {
        if (node->firstFace02 >= 0) {
            face = &query->faces04[node->firstFace02];
            do {
                if ((face->flags10 & 0x4000) == 0 &&
                    func_01ffd824(face, query) >= 0) {
                    hit = face;
                }
                faceFlags = face->flags10;
                face++;
            } while ((faceFlags & 0x8000) == 0);
        }

        if ((query->flags00 & 1) == 0) {
            rejectId = (s32)query->rejectId84;
            rejectMask = query->rejectMask88;
            workValue = 0;
            object = node->objects08;
            while (object != 0) {
                if (object->rejectId28 != (u32)rejectId &&
                    (object->rejectMask22 & rejectMask) == 0 &&
                    object->vtable1c->test08(object, query) >= 0) {
                    workValue = (u32)object;
                }
                object = object->next04;
            }
            if (workValue != 0) {
                hit = data_027e0774;
                ((CollisionObject *)workValue)->vtable1c->finish10(
                    (CollisionObject *)workValue, query, hit);
                data_027e0764.object08 = (CollisionObject *)workValue;
            }
        }


        nodeFlags = node->flags00;
        frame = data_027e06e0;
        if ((nodeFlags & 0xf00f) == 0) break;
        frameSize = frame->size0c;
        workValue = frame->centerX04;
        nextFrame = frame + 1;
        quarter = frameSize / 4;
        if (query->bound34 < (s32)workValue) {
            child = query->bound38 < frame->centerZ08 ? 0 : 2;
        } else {
            child = query->bound38 < frame->centerZ08 ? 1 : 3;
        }
        if ((nodeFlags & (0x1001 << child)) == 0) break;
        switch (child) {
        case 0:
            nextFrame->centerX04 = workValue - quarter;
            nextFrame->centerZ08 = frame->centerZ08 - quarter;
            break;
        case 1:
            nextFrame->centerX04 = workValue + quarter;
            nextFrame->centerZ08 = frame->centerZ08 - quarter;
            break;
        case 2:
            nextFrame->centerX04 = workValue - quarter;
            nextFrame->centerZ08 = frame->centerZ08 + quarter;
            break;
        default:
            nextFrame->centerX04 = workValue + quarter;
            nextFrame->centerZ08 = frame->centerZ08 + quarter;
        }
        node = node->children10[child];
        nextFrame->childIndex00 = child;
        data_027e06e0 = nextFrame;
    }
    return hit;
}
