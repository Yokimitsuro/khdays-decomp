typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* Hit report filled in here and handed to the victim's hit callback. */
struct HitInfo {
    int flags;          /* +0x00 */
    VecFx32 vPush;      /* +0x04 */
    int field_10;       /* +0x10 */
    int field_14;       /* +0x14 */
    u8 field_18;        /* +0x18 */
    void *pAttacker;    /* +0x1c */
    int field_20;       /* +0x20, written by the callback */
    int field_24;       /* +0x24, written by the callback */
};

/* 12-byte message posted to the attacker's message hook. */
struct HitMsg {
    u8 field_00;
    u8 field_01;
    u8 field_02;
    u8 field_03;
    u16 wId04;
    u16 field_06;
    int field_08;
};

struct HitSlotBits {
    u8 field_00;
    u8 field_01;
    u8 field_02_lo : 6;
    u8 field_02_b6 : 1;
    u8 field_02_hi : 1;
    u8 field_03;
};

struct HitTable {
    int field_00;
    struct HitSlotBits aSlots[1];
};

struct HitSlot {
    u8 field_00;
    u8 field_01;
    u8 kind;
    u8 field_03;
    u16 field_04;
};

struct Actor;

struct Victim {
    char pad000[2];
    u16 wId2;
    char pad004[0x1c4 - 4];
    int (*pfnHit1c4)(u16 id, struct HitInfo *info);
};

struct Actor {
    char pad000[0x24];
    void (*pMsgHook24)(struct Actor *actor, struct HitMsg *msg, int len);
    char pad028[0x1a0 - 0x28];
    struct HitTable *pHitTable1a0;
    char pad1a4[0x1c4 - 0x1a4];
    u8 field_1c4;
    char pad1c5[0x28c - 0x1c5];
    struct HitSlot aSlots28c[1];
    char pad292[0x364 - 0x292];
    int field_364;
    int field_368;
};

extern const struct HitMsg data_ov107_020cb674;
extern const struct HitMsg data_ov107_020cb680;

/*
 * Deliver a hit from attacker `a` (slot `mode` of actor `b`) to `victim`:
 * build a HitInfo, pass it to the victim's hit callback and return its result.
 * If the callback reports bit 1 and the slot kind is 4 or 8, post a
 * follow-up message to b's message hook.
 */
int func_ov107_020ca918(struct Victim *victim, struct Actor *a, struct Actor *b, int mode,
                        const VecFx32 *push, int flags)
{
    struct HitInfo info = {0};
    struct HitMsg msgA;
    struct HitMsg msgB;
    int result;
    struct HitSlot *slot;

    if (victim->pfnHit1c4 == 0) {
        return 0;
    }
    if (b->field_1c4 & 0xa) {
        return 0;
    }

    info.vPush = *push;
    info.field_10 = b->aSlots28c[mode].field_04;
    info.flags = flags | 1;
    info.pAttacker = a;

    if (b->pHitTable1a0 == 0) {
        info.field_14 = 0;
        result = victim->pfnHit1c4(victim->wId2, &info);
    } else {
        slot = &b->aSlots28c[mode];
        if (b->pHitTable1a0->aSlots[mode].field_02_b6 == 0) {
            info.flags |= 8;
        }
        if (slot->field_00 & 1) {
            info.flags |= 0x10;
        }
        if (slot->field_01 & 1) {
            info.flags |= 0x20;
        }
        if (slot->field_01 & 2) {
            info.flags |= 0x40;
        }
        info.field_14 = slot->kind;
        info.field_18 = slot->field_03;
        result = victim->pfnHit1c4(victim->wId2, &info);

        if (info.field_24 & 2) {
            if (slot->kind == 4 && b->field_368 != 0) {
                msgA = data_ov107_020cb674;
                msgA.wId04 = victim->wId2;
                if (b->pMsgHook24 != 0) {
                    b->pMsgHook24(b, &msgA, 0xc);
                }
            } else if (slot->kind == 8 && b->field_364 != 0) {
                msgB = data_ov107_020cb680;
                msgB.wId04 = victim->wId2;
                msgB.field_08 = info.field_20;
                if (b->pMsgHook24 != 0) {
                    b->pMsgHook24(b, &msgB, 0xc);
                }
            }
        }
    }
    return result;
}
