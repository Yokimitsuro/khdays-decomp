/* Whether the ov106 actor may act on its target reference: the base check (020ad114) must pass and the
 * +0x4f0 reference must be of kind 1; a kind-0x3f entity (+0x19c) whose item (+4) is above 1 does
 * not qualify. Twin of ov291 020cca78 with the extra entity test. */
typedef unsigned char u8;

struct TargetRef {
    u8 nKind;
    u8 nId;
    u8 nIndex;
    u8 pad4f3[1];
    int nMode;
    void *pEquip;
    u8 *pEntity;
    u8 *pItem;
};

struct Actor {
    u8 pad000[0x4f0];
    struct TargetRef ref;
};

extern int func_ov022_020ad114(struct Actor *pActor);

int func_ov106_020b79dc(struct Actor *pActor)
{
    struct TargetRef *ref;

    if (!func_ov022_020ad114(pActor))
        return 0;
    ref = &pActor->ref;
    if (ref != 0) {
        if (ref->nKind == 1)
            goto ok;
    }
    return 0;
ok:
    if (ref->pEntity[0x19c] == 0x3f && ref->pItem[4] > 1) {
        return 0;
    }
    return 1;
}
