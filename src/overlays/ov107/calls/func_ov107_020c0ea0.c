typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
typedef short s16;

typedef struct Ov107Object Ov107Object;
typedef struct Ov107Actor Ov107Actor;

typedef struct {
    unsigned int bit0 : 1;
    signed int bit1 : 1;
    signed int bit2 : 1;
    unsigned int rest : 29;
} Flags40;

typedef struct {
    u16 lo : 8;
    u16 hi : 8;
} Flags60;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    u8 id;
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 rest : 6;
    u8 mask;
    s8 mode;
    unsigned int ownerTag;
    Ov107Actor *pActor;
} Ov107Slot;

typedef struct {
    u8 pad00[0xa0];
    u8 *liveCounts;
} Ov107SpawnTable;

typedef struct {
    u8 pad00[4];
    Ov107SpawnTable *pTable;
    u8 pad08[0xa8 - 8];
    u8 listA8[0x20];
} Ov107SpawnOwner;

struct Ov107Actor {
    u8 pad000[0x40];
    Flags40 flags40;
    u8 pad044[0x1c];
    Flags60 flags60;
    u8 pad062[0x12];
    Vec3 position;
    int radius;
    u8 pad084[0x1cc - 0x84];
    int (*actionCallback)(Ov107Actor *, int);
    u8 pad1d0[0x2d4 - 0x1d0];
    Ov107Object *pSpawner;
};

struct Ov107Object {
    u8 pad000[4];
    Ov107SpawnOwner *pOwner;
    u8 pad008[0x44 - 8];
    void (*callback44)(Ov107Object *);
    u16 flags48;
    u8 pad04a[2];
    s16 count;
    u8 pad04e[2];
    Ov107Slot slots[1];
    u8 pad05c[0xf4 - 0x5c];
    void *field_f4;
    int field_f8;
    int field_fc;
    int field_100;
    Vec3 position104;
    int field_110;
    int field_114;
    int field_118;
};

extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern void VEC_Subtract(int *a, int *b, int *out);
extern int FX_Sqrt(int x);
extern int func_ov107_020cab14(Ov107Actor *actor, int *out);
extern s16 func_ov107_020c1c8c(Ov107Object *self);
extern int func_ov107_020c1c94(Ov107Object *self);
extern void func_ov107_020c1c18(Ov107Object *self, void *pAnim, int duration);
extern int func_ov107_020cb4f0(int obj, int arg);
extern void func_ov107_020c1870(Ov107Object *self, int arg);

void func_ov107_020c0ea0(Ov107Object *self, int delta)
{
    int timer;
    int bestDist;
    Ov107Actor *best;
    Ov107SpawnOwner *owner;
    int i;
    Ov107Actor *slotActor;
    Ov107SpawnTable *table;

    owner = self->pOwner;
    timer = self->field_fc;
    table = owner->pTable;
    if (timer > 0) {
        self->field_fc = timer - delta / 30;
        return;
    }

    if (self->field_114 > 0) {
        Ov107Actor *actor;
        int *pNode;

        bestDist = 0x7fffffff;
        best = 0;
        pNode = func_01fffd70(owner->listA8);
        actor = pNode == 0 ? 0 : (Ov107Actor *)*pNode;
        while (actor != 0) {
            if (actor->flags40.bit1 && actor->flags40.bit2
                && (actor->flags60.lo & 1) != 0) {
                Vec3 deltaVec;
                long long distSq;
                int scaledDist;

                VEC_Subtract((int *)&actor->position, (int *)&self->position104,
                             (int *)&deltaVec);
                distSq = (long long)deltaVec.x * deltaVec.x
                       + (long long)deltaVec.y * deltaVec.y
                       + (long long)deltaVec.z * deltaVec.z;
                scaledDist = (int)((distSq + 0x800) >> 12);
                if (scaledDist < bestDist) {
                    bestDist = scaledDist;
                    best = actor;
                }
            }
            pNode = func_01fffd8c(owner->listA8);
            actor = pNode == 0 ? 0 : (Ov107Actor *)*pNode;
        }

        if (best != 0 && FX_Sqrt(bestDist) < self->field_114 + best->radius) {

            for (i = 0; i < self->count; i++) {
                if (self->slots[i].bit1 && self->slots[i].bit0) {
                        slotActor = self->slots[i].pActor;
                        if (slotActor->flags40.bit1 && slotActor->flags40.bit2) {
                            int out;
                            if (func_ov107_020cab14(slotActor, &out) == 0) {
                                int result;
                                if (slotActor->actionCallback != 0) {
                                    result = slotActor->actionCallback(slotActor, 2);
                                } else {
                                    result = 0;
                                }
                                if (result != 0) {
                                    table->liveCounts[self->slots[i].id]--;
                                    self->slots[i].bit1 = 0;
                                    self->slots[i].pActor->pSpawner = 0;
                                    self->slots[i].pActor = 0;
                                }
                            }
                        }
                    }
            }
            self->field_100 = 0x3000;
        } else if ((timer = self->field_100) > 0) {
            self->field_100 = timer - delta / 30;
        } else {

        for (i = 0; i < self->count; i++) {
            if (self->slots[i].bit1 && self->slots[i].bit0) {
                    slotActor = self->slots[i].pActor;
                    if (slotActor->flags40.bit1 && slotActor->flags40.bit2) {
                        int result;
                        if (slotActor->actionCallback != 0) {
                            result = slotActor->actionCallback(slotActor, 2);
                        } else {
                            result = 0;
                        }
                        if (result != 0) {
                            table->liveCounts[self->slots[i].id]--;
                            self->slots[i].bit1 = 0;
                            self->slots[i].pActor->pSpawner = 0;
                            self->slots[i].pActor = 0;
                        }
                    }
                }
        }
        self->field_fc = 0x1000;
    }

    }

    if (self->field_f4 == 0)
        return;

    if ((self->flags48 & 1) == 0 && self->field_f8 <= 0) {
        if (func_ov107_020c1c8c(self) == func_ov107_020c1c94(self)) {
            void (*callback)(Ov107Object *);

            func_ov107_020c1c18(self, 0, 0);
            callback = self->callback44;
            if (callback != 0)
                callback(self);
            return;
        }
    }

    if (func_ov107_020cb4f0((int)self->field_f4, delta) != 0) {
        func_ov107_020c1870(self, 0);
        self->field_fc = 0x1000;
        if ((self->flags48 & 1) == 0)
            self->field_f8--;
    }
}
