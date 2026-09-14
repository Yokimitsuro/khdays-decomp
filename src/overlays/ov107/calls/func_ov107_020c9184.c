typedef struct Ov107ListNode {
    int field0;
    struct Ov107ListNode *next;
} Ov107ListNode;

typedef struct Ov107List {
    int field0;
    Ov107ListNode *head;
    int pad08;
    int pad0c;
    Ov107ListNode listhead;
    int pad18;
    int pad1c;
    int pad20;
    Ov107ListNode *cur;
} Ov107List;

typedef struct Ov107Manager {
    char pad00[0x80];
    Ov107List list;              /* +0x80 */
} Ov107Manager;

typedef struct Ov107SubObj {
    int field0;
    Ov107Manager *manager;       /* +0x4 */
    char pad08[0x60 - 8];
    unsigned short typeLow : 8;  /* +0x60, low byte tested */
    unsigned short typeHigh : 8;
    char pad62[0x1ac - 0x62];
    unsigned short state;        /* +0x1ac */
    char pad1ae[0x22c - 0x1ae];
    Ov107List subList;           /* +0x22c */
} Ov107SubObj;

typedef struct Ov107Query Ov107Query;

extern void **func_01fffd70(void *list);
extern void **func_01fffd8c(void *list);
extern int func_ov107_020c38ac(void *node, Ov107Query *query, void *pOutContact);

void *func_ov107_020c9184(Ov107SubObj *self, Ov107Query *query, void **out)
{
    void **ppNode;
    Ov107Manager *mgr;
    Ov107SubObj **ppEntity;
    Ov107SubObj *entity;

    mgr = self->manager;
    ppEntity = (Ov107SubObj **)func_01fffd70(&mgr->list);
    entity = (ppEntity == 0) ? 0 : *ppEntity;

    while (entity != 0) {
        if (entity != self && (entity->typeLow & 1) &&
            !(entity->state & 1) && !(entity->state & 2) && !(entity->state & 4)) {
            ppNode = (void **)func_01fffd70(&entity->subList);
            while (ppNode != 0) {
                if (func_ov107_020c38ac(*ppNode, query, 0) != 0) {
                    if (out != 0) {
                        *out = ppNode;
                    }
                    return entity;
                }
                ppNode = (void **)func_01fffd8c(&entity->subList);
            }
        }

        ppEntity = (Ov107SubObj **)func_01fffd8c(&mgr->list);
        entity = (ppEntity == 0) ? 0 : *ppEntity;
    }
    return 0;
}
