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
    void *pEntity;                /* 0x4fc */
    void *pItem;                 /* 0x500 */
    struct Node *pNode;          /* 0x504 */
};

struct Actor {
    u8 pad000[0x4f0];
    struct TargetRef ref;        /* 0x4f0 */
};

extern int func_ov022_020ad114(struct Actor *pActor);

int func_ov291_020cca78(struct Actor *pActor)
{
    struct TargetRef *ref;

    if (!func_ov022_020ad114(pActor))
        return 0;
    ref = &pActor->ref;
    /* The ROM has two real branches into one shared "return 0" tail. Written as
       `ref != 0 && ref->nKind == 1`, or as if/else, mwcc turns the tail into
       conditional moves instead, so the nested test and goto are deliberate. */
    if (ref != 0) {
        if (ref->nKind == 1)
            goto ok;
    }
    return 0;
ok:
    return 1;
}
