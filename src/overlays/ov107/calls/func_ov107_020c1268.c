/* Spawner teardown callback (installed at node+0x34 by func_ov107_020c0dd0): unless the owner is
 * flagged at +0xc8, walk every slot; for each slot with both flag bits set whose actor is live
 * (actor+0x1ac bit 1 clear, actor+0x60 bit 0 set), run the actor's +0x1f8 callback, decrement the
 * per-id live count, clear the slot's bit 1 and unlink actor and slot.
 * Layout of Ov107Object/Ov107Slot/Actor from func_ov107_020c1e80. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;

typedef struct Actor Actor;
typedef struct Ov107Object Ov107Object;

struct flags16 { u16 lo : 8, hi : 8; };

struct Actor {
    u8 pad000[0x60];
    struct flags16 field_60;        /* +0x60 */
    u8 pad062[0x1ac - 0x62];
    u16 field_1ac;                  /* +0x1ac */
    u8 pad1ae[0x1f8 - 0x1ae];
    void (*field_1f8)(Actor *self); /* +0x1f8 */
    u8 pad1fc[0x2d4 - 0x1fc];
    Ov107Object *pSpawner;          /* +0x2d4 */
};

typedef struct {
    u8 id;
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 rest : 6;
    u8 mask;
    s8 mode;
    u32 ownerTag;
    Actor *pActor;      /* +0x08 */
} Ov107Slot;

typedef struct {
    u8 pad00[0xa0];
    u8 *liveCounts;     /* +0xa0 */
} Ov107SpawnTable;

typedef struct {
    u8 pad00[4];
    Ov107SpawnTable *pTable; /* +0x04 */
    u8 pad08[0xc8 - 0x08];
    int field_c8;            /* +0xc8 */
} Ov107SpawnOwner;

struct Ov107Object {
    u8 pad00[4];
    Ov107SpawnOwner *pOwner; /* +0x04 */
    u8 pad08[0x44];
    s16 count;          /* +0x4c */
    u8 pad4e[2];
    Ov107Slot slots[1]; /* +0x50 */
};

void func_ov107_020c1268(Ov107Object *obj)
{
    int i;
    Ov107SpawnTable *table;

    if (obj->pOwner == 0)
        return;
    if (obj->pOwner->field_c8 != 0)
        return;

    table = obj->pOwner->pTable;
    for (i = 0; i < obj->count; i++) {
        Actor *actor;
        if (obj->slots[i].bit1 && obj->slots[i].bit0 && (actor = obj->slots[i].pActor) != 0 &&
            !(actor->field_1ac & 2) && (actor->field_60.lo & 1)) {
            if (actor->field_1f8 != 0)
                actor->field_1f8(actor);
            table->liveCounts[obj->slots[i].id]--;
            obj->slots[i].bit1 = 0;
            obj->slots[i].pActor->pSpawner = 0;
            obj->slots[i].pActor = 0;
        }
    }
}
