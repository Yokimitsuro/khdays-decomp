typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef int fx32;

typedef struct { fx32 x, y, z; } VecFx32;

static inline fx32 FX_Mul(fx32 a, fx32 b)
{
    return (fx32)(((long long)a * b + 0x800) >> 12);
}

struct HitSlotBits {
    u8 field_00;
    u8 field_01;
    u8 field_02_lo : 6;
    u8 field_02_b6 : 1;
    u8 field_02_hi : 1;
    u8 field_03;
};

/* Partial: only the fields this function reads. */
struct HitTable {
    int field_00;
    struct HitSlotBits aSlots[12];      /* +0x04 */
    s16 field_34[14];                   /* +0x34, one per bit of the hit's high flags */
    char pad50[0x5c - 0x50];
    u8 field_5c_b0 : 1;                 /* +0x5c */
    u8 field_5c_rest : 7;
};

struct Attack {
    char pad00[4];
    u8 field_04;                        /* indexes Actor.field_2bc */
};

/* Partial: an entry of the manager's list at +0x2c, the hit's source. */
typedef struct SourceActor {
    char pad000[0x19c];
    VecFx32 direction;                  /* +0x19c */
} SourceActor;

/* Partial actor taking the hit. */
typedef struct Actor {
    char pad000[0xa0];
    int rotation[4];                    /* +0x0a0, quaternion handed to func_0202f384 */
    char pad0b0[0x1a0 - 0xb0];
    struct HitTable *hitTable;          /* +0x1a0 */
    char pad1a4[0x1ac - 0x1a4];
    u16 field_1ac;                      /* +0x1ac */
    char pad1ae[0x1c4 - 0x1ae];
    u8 field_1c4;                       /* +0x1c4 */
    u8 field_1c5;                       /* +0x1c5 */
    char pad1c6[0x218 - 0x1c6];
    s16 field_218;                      /* +0x218 */
    s16 field_21a;                      /* +0x21a */
    char pad21c[0x2bc - 0x21c];
    s16 field_2bc[1];                   /* +0x2bc, indexed by Attack.field_04 */
    char pad2be[0x2f0 - 0x2be];
    int field_2f0;                      /* +0x2f0 */
} Actor;

struct HitEvent {
    unsigned int flagsLo : 16;          /* +0x00 */
    unsigned int flagsHi : 16;
    VecFx32 point;                      /* +0x04 */
    int field_10 : 16;                  /* +0x10, base amount */
    int field_12 : 16;                  /* +0x12, flat amount added after scaling */
    int field_14 : 16;                  /* +0x14, index into the manager's actor list */
    int field_16 : 16;
    struct Attack *attack;              /* +0x18 */
    int field_1c;
    int slot;                           /* +0x20, index into hitTable->aSlots */
};

extern char *OS_IsThreadAvailable_0x020c9848(void);
extern void func_0202f384(VecFx32 *out, const void *rotation, const VecFx32 *in);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int func_ov107_020c5c70(Actor *obj, fx32 p1, fx32 p2);
extern const VecFx32 data_02042258;
extern u8 data_0204c240;
extern u8 data_0204c254[];

/* Sum of field_34 over the bits set in `mask`, scaled by 16. */
static inline fx32 SumTableBits(Actor *self, int mask)
{
    fx32 sum = 0;
    int i;

    if (self->hitTable != 0) {
        for (i = 0; i < 14; i++) {
            if ((mask >> i) & 1) {
                sum += self->hitTable->field_34[i] << 4;
            }
        }
    }
    return sum;
}

/*
 * Works out how much a hit takes off `self` and returns it as a whole number.
 *
 * The multiplier is 3 when field_1c4 has 0x8 and the hit lacks flagsLo 0x8
 * with flagsHi 0x4, or field_1c4 has 0x2 and the hit lacks flagsLo 0x8 with
 * flagsHi 0x8; otherwise 1. When field_1c4 has 0x4 and field_2f0 is zero,
 * field_218 / 10 is added as a bonus and field_1c5 0x4 is cleared. With no
 * attack record the result is field_10 * multiplier + bonus.
 *
 * Hit flag 0x10, or field_1c4 0x10, takes nothing. If the hit's slot has its
 * table bit set and the source actor's direction points the same way as self's
 * rotated forward vector (dot product > 0, y ignored) while the hit has flag
 * 0x4, flag 0x4000 is raised and nothing is taken.
 *
 * Otherwise the amount is built in fx32 from field_10: through
 * func_ov107_020c5c70 under flag 0x4, reduced by the table's per-bit field_34
 * values under flag 0x8, averaged when both, floored at 1.0 under flag 0x4,
 * then field_12 is added. A negative amount, or a non-positive one while
 * field_1ac has 0x20, raises flag 0x80. The amount is multiplied, cut by
 * data_0204c254[7] percent when data_0204c240 has 0x2, and replaced by
 * field_21a when the hit has flag 0x1000 and the table's field_5c bit 0 is set.
 */
int func_ov107_020c89e8(Actor *self, struct HitEvent *hit)
{
    VecFx32 sourceDir;
    VecFx32 facing;
    int mult;
    int bonus;
    int flagsLo;
    int flagsHi;
    fx32 resist;
    fx32 sum;
    fx32 amount;

    flagsLo = (u16)hit->flagsLo;
    flagsHi = (u16)hit->flagsHi;
    resist = 0;
    bonus = 0;
    mult = 1;
    if (self->field_1c4 & 8) {
        if (!((hit->flagsLo & 8) && (hit->flagsHi & 4))) {
            mult = 3;
        }
    } else if (self->field_1c4 & 2) {
        if (!((hit->flagsLo & 8) && (hit->flagsHi & 8))) {
            mult = 3;
        }
    }
    if ((self->field_1c4 & 4) && self->field_2f0 == 0) {
        bonus = self->field_218 / 10;
        self->field_1c5 &= ~4;
    }

    if (hit->attack == 0) {
        return hit->field_10 * mult + bonus;
    }
    if (flagsLo & 0x10) {
        return 0;
    }
    if (self->field_1c4 & 0x10) {
        return 0;
    }

    if (self->hitTable != 0) {
        if (hit->slot >= 0 && self->hitTable->aSlots[hit->slot].field_02_hi) {
            int index = hit->field_14;
            if (index >= 0) {
                char *mgr = OS_IsThreadAvailable_0x020c9848();
                SourceActor *source = mgr != 0 ? ((SourceActor **)(mgr + 0x2c))[index] : 0;

                sourceDir = source->direction;
                sourceDir.y = 0;
                func_0202f384(&facing, self->rotation, &data_02042258);
                facing.y = 0;
                if (VEC_DotProduct(&sourceDir, &facing) > 0 && (hit->flagsLo & 4)) {
                    hit->flagsLo |= 0x4000;
                    return 0;
                }
            }
        }
        resist = self->field_2bc[hit->attack->field_04] << 12;
    }

    if (flagsLo & 4) {
        if (flagsLo & 8) {
            sum = SumTableBits(self, flagsHi);
            amount = func_ov107_020c5c70(self, hit->field_10 << 12, resist);
            amount = (amount + FX_Mul(hit->field_10 << 12, 0x1000 - sum)) >> 1;
        } else {
            amount = func_ov107_020c5c70(self, hit->field_10 << 12, resist);
        }
    } else if (flagsLo & 8) {
        /* Same sum as SumTableBits, written out: the ROM reads the table
         * pointer once before the loop here, which colours the pointer and
         * the counter the other way round from the helper's form. */
        struct HitTable *table = self->hitTable;
        int i;

        sum = 0;
        if (table != 0) {
            for (i = 0; i < 14; i++) {
                if ((flagsHi >> i) & 1) {
                    sum += table->field_34[i] << 4;
                }
            }
        }
        amount = FX_Mul(hit->field_10 << 12, 0x1000 - sum);
    } else {
        amount = 0;
    }
    if ((flagsLo & 4) && amount < 0x1000) {
        amount = 0x1000;
    }
    amount += hit->field_12 << 12;
    if (amount < 0) {
        hit->flagsLo |= 0x80;
    }
    if (amount <= 0 && (self->field_1ac & 0x20)) {
        hit->flagsLo |= 0x80;
    }
    amount *= mult;
    if ((data_0204c240 & 2) && data_0204c254[7] != 0) {
        amount -= amount * data_0204c254[7] / 100;
    }
    if ((hit->flagsLo & 0x1000) && self->hitTable != 0 && self->hitTable->field_5c_b0) {
        amount = self->field_21a << 12;
    }
    return bonus + ((amount + 0x800) >> 12);
}
