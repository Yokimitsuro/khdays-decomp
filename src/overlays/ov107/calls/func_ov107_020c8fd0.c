typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

typedef struct Sphere {
    Vec3 pos;
    int radius;
} Sphere;

typedef struct Ov264ListNode {
    int field0;
    struct Ov264ListNode *next;
} Ov264ListNode;

typedef struct Ov264List {
    int field0;
    Ov264ListNode *head;
    int pad08;
    int pad0c;
    Ov264ListNode listhead;
    int pad18;
    int pad1c;
    int pad20;
    Ov264ListNode *cur;
} Ov264List;

typedef struct Ov264Entity {
    int field0;
    void *manager;          /* +0x4, must match the owning manager for the entity to be live */
    char pad08[0x74 - 8];
    Sphere sphere;           /* +0x74 */
} Ov264Entity;

typedef struct Ov264Manager {
    char pad00[0xa8];
    Ov264List list;          /* +0xa8 */
} Ov264Manager;

typedef struct Ov264Owner {
    int field0;
    Ov264Manager *manager;   /* +0x4 */
} Ov264Owner;

typedef struct Ov264Params Ov264Params;

extern void **func_01fffd70(void *list);
extern void **func_01fffd8c(void *list);
extern int func_020372cc(Vec3 *pos, Ov264Params *params);
extern int FX_Sqrt(int x);

int func_ov107_020c8fd0(Ov264Owner *owner, Ov264Params *params, void **out)
{
    Ov264Manager *mgr = owner->manager;
    Ov264Entity **ppEntity;
    Ov264Entity *entity;
    int count = 0;

    ppEntity = (Ov264Entity **)func_01fffd70(&mgr->list);
    entity = (ppEntity == 0) ? 0 : *ppEntity;
    while (entity != 0) {
        Sphere s = entity->sphere;
        if (entity->manager == owner->manager) {
            if (FX_Sqrt(func_020372cc(&s.pos, params)) <= s.radius) {
                out[count++] = entity;
            }
        }
        ppEntity = (Ov264Entity **)func_01fffd8c(&mgr->list);
        entity = (ppEntity == 0) ? 0 : *ppEntity;
    }
    return count;
}
