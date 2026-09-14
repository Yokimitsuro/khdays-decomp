/* Releases the spawner slot held by an actor: finds the slot whose actor is
 * this one, notifies ov002 of the retirement, decrements the per-id live
 * count, clears the slot's two flag bits and unlinks actor and slot. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;

typedef struct Actor Actor;
typedef struct Ov107Object Ov107Object;

struct Actor {
    u8 pad000[0x2d4];
    Ov107Object *pSpawner; /* +0x2d4 */
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
} Ov107SpawnOwner;

struct Ov107Object {
    u8 pad00[4];
    Ov107SpawnOwner *pOwner; /* +0x04 */
    u8 pad08[0x44];
    s16 count;          /* +0x4c */
    u8 pad4e[2];
    Ov107Slot slots[1]; /* +0x50 */
};

extern void func_ov002_020730e4(Actor *pActor);

void func_ov107_020c1e80(Actor *actor)
{
    Ov107Object *obj = actor->pSpawner;
    int i;

    if (obj == 0 || obj->pOwner == 0 || obj->pOwner->pTable == 0)
        return;

    for (i = 0; i < obj->count; i++) {
        if (obj->slots[i].pActor == actor) {
            Ov107SpawnTable *table = obj->pOwner->pTable;
            func_ov002_020730e4(actor);
            table->liveCounts[obj->slots[i].id]--;
            obj->slots[i].bit0 = 0;
            obj->slots[i].bit1 = 0;
            obj->slots[i].pActor->pSpawner = 0;
            obj->slots[i].pActor = 0;
            return;
        }
    }
}
