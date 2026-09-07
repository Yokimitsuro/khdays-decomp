/* ov022: check the actor's target reference is still good, and drop it if not.
 *
 * Only the two kinds that name something outside the actor can go stale: an
 * equip command the scene may have retired, and a node that may have emptied.
 * The kind that walks an entity's own list is left alone. A stale reference has
 * its kind cleared, which is what makes the answer false.
 *
 * While the actor is in state 5 the reference is not checked at all and the
 * answer is false regardless.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Node {
    u8 pad00[0x12];
    u16 nCount;                  /* 0x12 */
};

struct TargetRef {
    u8 nKind;                    /* 0x4f0 */
    u8 nId;                      /* 0x4f1 */
    u8 nIndex;                   /* 0x4f2 */
    u8 pad4f3[1];
    int nMode;                   /* 0x4f4 */
    void *pEquip;                /* 0x4f8 */
    void *pEntity;               /* 0x4fc */
    void *pItem;                 /* 0x500 */
    struct Node *pNode;          /* 0x504 */
};

struct Actor {
    u8 pad000[0x4f0];
    struct TargetRef ref;        /* 0x4f0 */
};

extern int func_ov022_0209bd04(struct Actor *pActor);
extern void *func_ov002_0207679c(int nIndex, int nId);
extern int func_ov002_02076d24(void *pEquip);
extern struct Node *func_01fffde0(int nId);

int func_ov022_020ad114(struct Actor *pActor)
{
    int bStale;

    bStale = 0;
    if (func_ov022_0209bd04(pActor) == 5) {
        return bStale;
    }
    switch (pActor->ref.nKind) {
    case 1:
        break;
    case 2:
        pActor->ref.pEquip = func_ov002_0207679c(pActor->ref.nIndex,
                                                 pActor->ref.nId);
        bStale = 1;
        if (pActor->ref.pEquip != 0) {
            if (func_ov002_02076d24(pActor->ref.pEquip) != 0) {
                bStale = 0;
            }
        }
        break;
    case 3:
        pActor->ref.pNode = func_01fffde0(pActor->ref.nId);
        if (pActor->ref.pNode->nCount == 0) {
            bStale = 1;
        }
        break;
    default:
        break;
    }
    if (bStale != 0) {
        pActor->ref.nKind = 0;
    }
    return pActor->ref.nKind != 0;
}
