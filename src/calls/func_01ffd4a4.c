typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct CollisionFace88 CollisionFace88;
typedef struct CollisionRayQuery CollisionRayQuery;
typedef struct CollisionObject CollisionObject;

typedef struct CollisionObjectVtable {
    void *slot00;
    void *slot04;
    s32 (*test08)(CollisionObject *, CollisionRayQuery *);
    void *slot0c;
    void (*finish10)(CollisionObject *, CollisionRayQuery *, void *);
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

struct CollisionRayQuery {
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

typedef struct CollisionGlobalHit {
    u32 pad00[2];
    CollisionObject *object08;
} CollisionGlobalHit;

extern s32 func_01ffd184(CollisionFace88 *, CollisionRayQuery *);
extern u8 data_027e0774[];
extern CollisionGlobalHit data_027e0764;
extern CollisionTraversalFrame *data_027e06e0;
extern CollisionTraversalFrame data_027e06e4;

void *func_01ffd4a4(CollisionNode *node, CollisionRayQuery *query)
{
    void *hit = 0;
    CollisionFace88 *face;
    CollisionObject *object;
    u32 workValue;
    s32 frameSize;
    CollisionTraversalFrame *frame;
    u16 nodeFlags;
    s32 descentChild;
    CollisionTraversalFrame *nextFrame;
    CollisionTraversalFrame *parentFrame;
    u16 faceFlags;
    u16 siblingFlags;
    u16 rejectMask;
    s32 rejectId;
    s32 quarter;
    s16 previousChild;

restart:
    if (node->firstFace02 >= 0) {
        face = &query->faces04[node->firstFace02];
        do {
            if ((face->flags10 & 0x4000) == 0 &&
                func_01ffd184(face, query) >= 0) {
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
    if ((nodeFlags & 0xf00f) == 0) {
        goto ascend;
    }

    {
    nextFrame = frame + 1;
    frameSize = frame->size0c;
    workValue = (u32)frame->centerX04;
    quarter = frameSize / 4;
    if (query->bound3c < (s32)workValue) {
        nodeFlags &= 0x5555;
    } else if (query->bound34 > (s32)workValue) {
        nodeFlags &= 0xaaaa;
    }
    if (query->bound40 < frame->centerZ08) {
        nodeFlags &= 0x3333;
    } else if (query->bound38 > frame->centerZ08) {
        nodeFlags &= 0xcccc;
    }

    descentChild = 0xf;
    if ((nodeFlags & 0x1001) != 0) {
        nextFrame->centerX04 = (s32)workValue - quarter;
        descentChild = 0;
        nextFrame->centerZ08 = frame->centerZ08 - quarter;
    } else if ((nodeFlags & 0x2002) != 0) {
        nextFrame->centerX04 = (s32)workValue + quarter;
        descentChild = 1;
        nextFrame->centerZ08 = frame->centerZ08 - quarter;
    } else if ((nodeFlags & 0x4004) != 0) {
        nextFrame->centerX04 = (s32)workValue - quarter;
        descentChild = 2;
        nextFrame->centerZ08 = frame->centerZ08 + quarter;
    } else if ((nodeFlags & 0x8008) != 0) {
        nextFrame->centerX04 = (s32)workValue + quarter;
        descentChild = 3;
        nextFrame->centerZ08 = frame->centerZ08 + quarter;
    }

    if (descentChild != 0xf) {
        node = node->children10[descentChild];
        nextFrame->childIndex00 = (s16)descentChild;
        frame->nodeFlags02 = nodeFlags;
        data_027e06e0 = nextFrame;
        goto restart;
    }
    }

ascend:
    while (frame != &data_027e06e4) {
        previousChild = frame->childIndex00;
        if (previousChild == 3) {
            frame--;
            node = node->parent0c;
            continue;
        }

        parentFrame = frame - 1;
        node = node->parent0c;
        siblingFlags = parentFrame->nodeFlags02;

        {
        s32 siblingChild;
        quarter = parentFrame->size0c / 4;
        siblingChild = 0;

        if (previousChild == 0) {
            goto try_child1;
        }
        if (previousChild == 1) {
            goto try_child2;
        }
        if (previousChild != 2) {
            goto sibling_done;
        }
        goto try_child3;

try_child1:
        if ((siblingFlags & 0x2002) != 0) {
            siblingChild = 1;
            frame->centerX04 = parentFrame->centerX04 + quarter;
            frame->centerZ08 = parentFrame->centerZ08 - quarter;
            goto sibling_done;
        }

try_child2:
        if ((siblingFlags & 0x4004) != 0) {
            siblingChild = 2;
            frame->centerX04 = parentFrame->centerX04 - quarter;
            frame->centerZ08 = parentFrame->centerZ08 + quarter;
            goto sibling_done;
        }

try_child3:
        if ((siblingFlags & 0x8008) != 0) {
            siblingChild = 3;
            frame->centerX04 = parentFrame->centerX04 + quarter;
            frame->centerZ08 = parentFrame->centerZ08 + quarter;
        }

sibling_done:
        if (siblingChild != 0) {
            node = node->children10[siblingChild];
            frame->childIndex00 = (s16)siblingChild;
            data_027e06e0 = frame;
            goto restart;
        }
        frame--;
        }
    }

    return hit;
}
