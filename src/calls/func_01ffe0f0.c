/* Quadtree traversal for the model spatial-face ray test. */
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct CollisionFace84 CollisionFace84;
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
    s16 unknown04;
    s16 firstSpatialFace06;
    CollisionObject *objects08;
    struct CollisionNode *parent0c;
    struct CollisionNode *children10[4];
} CollisionNode;

struct CollisionFace84 {
    u8 pad00[16];
    u16 flags10;
    u16 vertexCount12;
    u8 rest14[0x84 - 0x14];
};

struct CollCastState {
    u32 flags00;
    u8 pad04[8];
    CollisionFace84 *faces0c;
    u8 pad10[0x34 - 0x10];
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


extern s32 func_01ffdd58(CollisionFace84 *, CollCastState *);
extern CollisionTraversalFrame *data_027e06e0;
extern CollisionTraversalFrame data_027e06e4;

void *func_01ffe0f0(CollisionNode *node, CollCastState *query)
{
    void *hit = 0;
    CollisionFace84 *face;
    u32 workValue;
    s32 frameSize;
    CollisionTraversalFrame *frame;
    u16 nodeFlags;
    s32 descentChild;
    CollisionTraversalFrame *nextFrame;
    CollisionTraversalFrame *parentFrame;
    u16 faceFlags;
    u16 siblingFlags;
    s32 quarter;
    s16 previousChild;

restart:
    if (node->firstSpatialFace06 >= 0) {
        face = &query->faces0c[node->firstSpatialFace06];
        do {
            if ((face->flags10 & 0x4000) == 0 &&
                func_01ffdd58(face, query) >= 0) {
                hit = face;
            }
            faceFlags = face->flags10;
            face++;
        } while ((faceFlags & 0x8000) == 0);
    }

    nodeFlags = node->flags00;
    frame = data_027e06e0;
    if ((nodeFlags & 0xf00) == 0) {
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
    if ((nodeFlags & 0x100) != 0) {
        nextFrame->centerX04 = (s32)workValue - quarter;
        descentChild = 0;
        nextFrame->centerZ08 = frame->centerZ08 - quarter;
    } else if ((nodeFlags & 0x200) != 0) {
        nextFrame->centerX04 = (s32)workValue + quarter;
        descentChild = 1;
        nextFrame->centerZ08 = frame->centerZ08 - quarter;
    } else if ((nodeFlags & 0x400) != 0) {
        nextFrame->centerX04 = (s32)workValue - quarter;
        descentChild = 2;
        nextFrame->centerZ08 = frame->centerZ08 + quarter;
    } else if ((nodeFlags & 0x800) != 0) {
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
        if ((siblingFlags & 0x200) != 0) {
            siblingChild = 1;
            frame->centerX04 = parentFrame->centerX04 + quarter;
            frame->centerZ08 = parentFrame->centerZ08 - quarter;
            goto sibling_done;
        }

try_child2:
        if ((siblingFlags & 0x400) != 0) {
            siblingChild = 2;
            frame->centerX04 = parentFrame->centerX04 - quarter;
            frame->centerZ08 = parentFrame->centerZ08 + quarter;
            goto sibling_done;
        }

try_child3:
        if ((siblingFlags & 0x800) != 0) {
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
