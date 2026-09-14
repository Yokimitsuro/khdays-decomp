/* Spawner command dispatch for an Ov107Object.
 *
 * op 0: for every enabled slot without an actor, ask func_ov107_020c1744 for a
 *       matching free actor; bind it to the slot, reset it (+0x21a from +0x218,
 *       clamped at zero; +0x1c5 bits), hand it the slot's data block, queue
 *       mode, status byte and owner tag, place it at the spawner position (or
 *       the zero vector when flag 4 is set), and collect it in a list that is
 *       passed to func_ov107_020c1370 and then destroyed.
 * op 1: for every bound slot whose actor is live (+0x60 bit 0 set, +0x1ac
 *       bit 1 clear), ask the actor's +0x1cc callback with 1; on yes unbind.
 * op 2: as op 1 without the +0x60 test, callback argument 2, and the per-id
 *       live count is decremented on unbind.
 * Layout of Ov107Object/Ov107Slot from func_ov107_020c1e80, func_ov107_020c1d3c,
 * func_ov107_020c1e24 and func_ov107_020c0dd0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct AiState AiState;
typedef struct Ov107Object Ov107Object;

struct flags16 { u16 lo : 8, hi : 8; };

/* An s16 kept in [0, max] by its setter. func_ov286_020d3a68 and its ov285/ov294-296/ov147
 * siblings clamp +0x21a into [0, +0x218] the same way; that those objects are this one is
 * not established. */
typedef struct {
    s16 max;      /* +0x0 */
    s16 value;    /* +0x2 */
} ClampedS16;

/* Partial. */
struct AiState {
    u8 pad000[0x38];
    void (*field_38)(AiState *self, int size, void *data);     /* +0x038 */
    u8 pad03c[0x60 - 0x3c];
    struct flags16 flags60;                                     /* +0x060 */
    u8 pad062[0x1ac - 0x62];
    u16 field_1ac;                                              /* +0x1ac */
    u16 flags1ae;                                               /* +0x1ae */
    u8 pad1b0[0x1c5 - 0x1b0];
    u8 field_1c5;                                               /* +0x1c5 */
    u8 pad1c6[3];
    s8 field_1c9;                                               /* +0x1c9 */
    u8 pad1ca[2];
    int (*field_1cc)(AiState *self, int op);                    /* +0x1cc */
    u8 pad1d0[0x1e8 - 0x1d0];
    void (*field_1e8)(AiState *self);                           /* +0x1e8 release */
    u8 pad1ec[0x1f4 - 0x1ec];
    void (*field_1f4)(AiState *self, const VecFx32 *pos, int field_110); /* +0x1f4 */
    u8 pad1f8[0x218 - 0x1f8];
    ClampedS16 pair218;                                         /* +0x218 */
    u8 pad21c[0x2d0 - 0x21c];
    u32 field_2d0;                                              /* +0x2d0 owner tag */
    Ov107Object *pSpawner;                                      /* +0x2d4 */
};

typedef struct {
    u8 id;
    u8 bit0 : 1;        /* slot enabled */
    u8 bit1 : 1;        /* an actor is bound */
    s8 dataIndex : 4;   /* index into dataBlocks, negative for none */
    u8 rest : 2;
    u8 mask;
    s8 mode;
    u32 ownerTag;
    AiState *pActor;    /* +0x08 */
} Ov107Slot;

typedef struct {
    void *data;
    int size;
} Ov107DataBlock;

typedef struct {
    u8 pad00[0xa0];
    u8 *liveCounts;     /* +0xa0 */
} Ov107SpawnTable;

typedef struct {
    u8 pad00[4];
    Ov107SpawnTable *pTable; /* +0x04 */
} Ov107SpawnOwner;

typedef struct {
    u8 pad00[0xc];
    int lo : 16;        /* +0x0c */
    int bitIndex : 3;   /* +0x0c bits 16-18, negative for none */
    int hi : 13;
} Ov107F4;

struct Ov107Object {
    u8 pad00[4];
    Ov107SpawnOwner *pOwner;      /* +0x004 */
    u8 pad08[0x48 - 0x08];
    u16 flags48;                  /* +0x048 */
    u8 pad4a[2];
    s16 count;                    /* +0x04c */
    u8 pad4e[2];
    Ov107Slot slots[8];           /* +0x050 */
    s16 dataCount;                /* +0x0b0 */
    u8 padb2[2];
    Ov107DataBlock dataBlocks[8]; /* +0x0b4 */
    Ov107F4 *field_f4;            /* +0x0f4 */
    u8 padf8[0x104 - 0xf8];
    VecFx32 spawnPos;             /* +0x104 */
    int field_110;                /* +0x110 */
};

/* List header, 0x28 bytes, built by func_01fffc24. */
typedef struct {
    u32 words[10];
} SpawnList;

extern void func_01fffc24(SpawnList *list);
extern AiState *func_ov107_020c1744(Ov107Object *obj, int index);
extern void func_ov107_020c5c14(AiState *actor, u8 status);
extern void *func_01fffca8(SpawnList *list, int extra, u32 key);
extern void func_ov107_020c1370(Ov107Object *obj, SpawnList *list);
extern void NNSi_FndDestroyDoubleList(SpawnList *list);
extern void func_ov107_020c1e80(AiState *actor);
extern const VecFx32 data_02041dc8;

static inline void AiState_PassData(AiState *actor, int size, void *data)
{
    if (actor->field_38 != 0)
        actor->field_38(actor, size, data);
}

static inline void AiState_Place(AiState *actor, const VecFx32 *pos, int field_110)
{
    if (actor->field_1f4 != 0)
        actor->field_1f4(actor, pos, field_110);
}

static inline int AiState_Call1cc(AiState *actor, int op)
{
    return actor->field_1cc != 0 ? actor->field_1cc(actor, op) : 0;
}

/* Clamp v into [lo, hi]. The upper bound is unsigned: with a signed bound the
 * compiler proves the upper test dead when v and hi are the same field and
 * deletes it, while the ROM keeps that compare (a dead `cmp r1, r1`). The type
 * is inferred from that one fact. With lo >= 0 it behaves as a signed clamp.
 * func_ov107_020c2364 clamps the same fields with the same routine. */
static inline int ClampRange(int v, int lo, unsigned int hi)
{
    if (v < lo)
        return lo;
    if (v > hi)
        return hi;
    return v;
}

void func_ov107_020c1870(Ov107Object *obj, int op)
{
    SpawnList list;
    Ov107SpawnTable *table;
    int i;

    table = 0;
    if (obj->pOwner != 0)
        table = obj->pOwner->pTable;

    switch (op) {
    case 0:
        func_01fffc24(&list);
        for (i = 0; i < obj->count; i++) {
            AiState *actor;
            Ov107DataBlock *blocks;
            int index;

            if (obj->slots[i].bit1 || !obj->slots[i].bit0)
                continue;
            actor = func_ov107_020c1744(obj, i);
            if (actor == 0)
                continue;

            /* Refill the timer to its maximum through the usual [0, max] clamp. */
            actor->pair218.value = ClampRange(actor->pair218.max, 0, actor->pair218.max);

            actor->field_1c5 &= ~0x17;
            if (obj->field_f4 != 0) {
                int bit = obj->field_f4->bitIndex;
                if (bit >= 0)
                    actor->field_1c5 |= (u8)(1 << bit);
            }
            blocks = obj->dataBlocks;
            index = obj->slots[i].dataIndex;
            if (index >= 0) {
                Ov107DataBlock *block = &blocks[index];
                AiState_PassData(actor, block->size, block->data);
            }
            obj->slots[i].pActor = actor;
            obj->slots[i].bit1 = 1;
            actor->field_1e8 = func_ov107_020c1e80;
            actor->pSpawner = obj;
            actor->field_2d0 = obj->slots[i].ownerTag;
            if (obj->slots[i].mode >= 0)
                actor->field_1c9 = obj->slots[i].mode;
            func_ov107_020c5c14(actor, obj->slots[i].mask);
            if (obj->flags48 & 2)
                actor->flags1ae |= 0x100;
            else
                actor->flags1ae &= ~0x100;
            if (!(obj->flags48 & 4))
                AiState_Place(actor, &obj->spawnPos, obj->field_110);
            else
                AiState_Place(actor, &data_02041dc8, 0);
            *(AiState **)func_01fffca8(&list, 4, 100) = actor;
        }
        func_ov107_020c1370(obj, &list);
        NNSi_FndDestroyDoubleList(&list);
        break;

    case 1:
        for (i = 0; i < obj->count; i++) {
            AiState *actor;

            if (!obj->slots[i].bit1 || !obj->slots[i].bit0 || (actor = obj->slots[i].pActor) == 0)
                continue;
            if (!(actor->flags60.lo & 1) || (actor->field_1ac & 2))
                continue;
            if (AiState_Call1cc(actor, 1)) {
                obj->slots[i].bit1 = 0;
                obj->slots[i].pActor->pSpawner = 0;
                obj->slots[i].pActor = 0;
            }
        }
        break;

    case 2:
        for (i = 0; i < obj->count; i++) {
            AiState *actor;

            if (!obj->slots[i].bit1 || !obj->slots[i].bit0 || (actor = obj->slots[i].pActor) == 0)
                continue;
            if (actor->field_1ac & 2)
                continue;
            if (AiState_Call1cc(actor, 2)) {
                table->liveCounts[obj->slots[i].id]--;
                obj->slots[i].bit1 = 0;
                obj->slots[i].pActor->pSpawner = 0;
                obj->slots[i].pActor = 0;
            }
        }
        break;
    }
}
