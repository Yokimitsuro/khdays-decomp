/* ov022: load the actor's six effect files and attach them to its render slots.
 *
 * Every pointer is cleared first, so a file the archive refuses is left null
 * rather than holding whatever it held last time.
 *
 * The archive entry is built rather than looked up: a base the actor carries,
 * biased and rounded down to a multiple of four, shifted up to leave room for
 * the slot number, with the top bit set to mark the kind. Only the slot number
 * changes from one to the next, so the six files are consecutive entries.
 *
 * The sixth is the same work written out again rather than a sixth pass,
 * because one model does not get it.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SLOT_COUNT 6
#define ID_BIAS 0x8000
#define ID_ALIGN 0xfffffc
#define ID_SHIFT 7
#define ID_KIND 0x80000000
#define ID_SLOT_MASK 0x1ff
#define LAYER_BIAS 7
#define MODEL_NO_TAIL 2

/* Ov022ActorNode */
struct ActorNode {
    u32 nFlags;                  /* 0x00 */
    u16 nAnimFlags;              /* 0x04 */
    u8 pad06[2];
};

/* Ov022RenderSlot -- one entry of the actor's render slot table */
struct RenderSlot {
    u8 pad00[0x24];
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[2];
    int nModelId;                /* 0x000c */
    u8 pad0010[0x10];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad0024[0x2a9c];
    struct RenderSlot aRenderSlots[SLOT_COUNT]; /* 0x2ac0 */
    void *apEffectFiles[SLOT_COUNT];            /* 0x2b98 */
    u8 pad2bb0[0x20];
    int nArchiveBase;            /* 0x2bd0 */
};

/* Archive_LoadFile */
extern void *func_0201ef9c(u32 nEntry, int nHeap);
extern void func_0202a3cc(struct RenderSlot *pSlot, u16 *pAnimFlags,
                          void *pFile, int nHeap);

void func_ov022_02097bd8(struct Actor *pActor)
{
    int i;

    for (i = 0; i < SLOT_COUNT; i++) {
        pActor->apEffectFiles[i] = 0;
    }
    for (i = 0; i < SLOT_COUNT - 1; i++) {
        pActor->apEffectFiles[i] = func_0201ef9c(
            (((pActor->nArchiveBase + ID_BIAS) & ID_ALIGN) << ID_SHIFT) | ID_KIND
            | (i & ID_SLOT_MASK), pActor->nId + LAYER_BIAS);
        func_0202a3cc(&pActor->aRenderSlots[i], &pActor->pNode->nAnimFlags,
                      pActor->apEffectFiles[i], pActor->nId + LAYER_BIAS);
    }
    if (pActor->nModelId == MODEL_NO_TAIL) {
        return;
    }
    pActor->apEffectFiles[SLOT_COUNT - 1] = func_0201ef9c(
        (((pActor->nArchiveBase + ID_BIAS) & ID_ALIGN) << ID_SHIFT) | ID_KIND
        | ((SLOT_COUNT - 1) & ID_SLOT_MASK), pActor->nId + LAYER_BIAS);
    func_0202a3cc(&pActor->aRenderSlots[SLOT_COUNT - 1],
                  &pActor->pNode->nAnimFlags,
                  pActor->apEffectFiles[SLOT_COUNT - 1],
                  pActor->nId + LAYER_BIAS);
}
