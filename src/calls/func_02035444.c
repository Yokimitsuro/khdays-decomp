#pragma thumb on
/* func_02035444 -- rebuild a party member's derived data, MAIN (THUMB). Loads the member's growth
 * table (func_020342e8, db 0x1d, row by class -- classes 0x13/0x14 use row 0, 0x15 row 0xe), scales
 * two of the member's stats (the third one x3 clamped to 0..255, the first one halved or scaled by
 * 0x666 depending on data_0204c240 bit 1) and writes them back to the record (data_0204c678, 0x104
 * bytes each) together with the display part. Every growth entry whose level (+0x20) is reached by
 * the current level (field 9) grants its reward (from data_020421b8): rewards 1..15 through
 * func_02035794 (with a 0x63 limit, lifted for 1..12 when game field 0x35bf is 2), the rest through
 * func_020358c0. Three fixed rewards (data_02042154) follow through func_02035830 (reward 4 skipped
 * when field 0x35bf is 2). Finally the member's movement block gets its base values and speed
 * 0x14000, the table is released and db 0x1d closed. The fixed-rewards loop is a do-while whose
 * first store alone is guarded by `i < 3` (always true), which is the ROM's in-loop bge; the
 * indexed reward of the else call is reread (volatile read). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RecHeader {
    u8 pad00[3];
    u8 kind;                            /* +0x03 */
    u8 icon;                            /* +0x04 */
    u8 pad05;
    u16 stat;                           /* +0x06 */
} RecHeader;

typedef struct Stat16 {
    u16 s0;                             /* +0x00 */
    u16 s1;                             /* +0x02 */
    u16 s2;                             /* +0x04 */
    u16 s3;                             /* +0x06 */
    u32 s8;                             /* +0x08 */
    u32 sc;                             /* +0x0c */
} Stat16;

typedef struct MemberRec {
    RecHeader hdr;                      /* +0x00 */
    Stat16 stats;                       /* +0x08 */
    char rest[0x104 - 0x18];
} MemberRec;

typedef struct RewardList {
    int id[24];
} RewardList;

typedef struct FixedRewards {
    int id[3];
} FixedRewards;

typedef struct GrowthEntry {
    int value;                          /* +0x00 */
    int level;                          /* +0x04 */
} GrowthEntry;

typedef struct GrowthTable {
    char pad00[0x10];
    int base10;                         /* +0x10 */
    int base14;                         /* +0x14 */
    int base18;                         /* +0x18 */
    GrowthEntry entry[24];              /* +0x1c */
} GrowthTable;

typedef struct { int x, y, z; } VecFx32;

static inline void VEC_Set(VecFx32 *a, int x, int y, int z)
{
    a->x = x;
    a->y = y;
    a->z = z;
}

typedef struct Mover {
    char pad00[0x14];
    int speed;                          /* +0x14 */
    char pad18[0x1c - 0x18];
    int base1c;                         /* +0x1c */
    char pad20[0x2c - 0x20];
    VecFx32 pos;                        /* +0x2c */
} Mover;

extern MemberRec data_0204c678[];
extern u8 data_0204c240;
extern const RewardList data_020421b8;
extern const FixedRewards data_02042154;

extern Mover *func_020358a4(int index);
extern void func_020353e0(int member, int a, int cls, int b);
extern void func_02035278(int member);
extern void func_02034150(int db, int mode);
extern void func_020342e8(GrowthTable **out, int db, int row, int mode);
extern int func_02005418(int value, int scale);
extern int func_020235d0(int field, int width);                  /* GameState_GetField */
extern void func_02035794(int member, int slot, u8 value, u8 *pair);
extern void func_020358c0(int member, int reward, int value);
extern void func_02035830(int member, u16 *pos);
extern void func_020343cc(GrowthTable **table);
extern void func_02034258(int db);

void func_02035444(int member, int a, int cls, int b)
{
    RewardList rewards;
    Stat16 stats;
    FixedRewards fixed;
    GrowthTable *table = 0;
    Mover *mover;
    MemberRec *rec;
    int level;
    int k;
    int i;

    mover = func_020358a4(member - 1);
    func_020353e0(member, a, cls, b);
    func_02035278(member);
    {
        RecHeader hdr;
        u16 aPos[2];
        u8 aPair[2];

        rec = &data_0204c678[member];
        stats = rec->stats;
        hdr = rec->hdr;
        func_02034150(0x1d, 2);
        switch (cls) {
        case 0x13:
            cls = 0;
            break;
        case 0x14:
            cls = 0;
            break;
        case 0x15:
            cls = 0xe;
            break;
        }
        func_020342e8(&table, 0x1d, cls, 2);
        {
            int v = stats.s3 * 3;

            if (v > 0xff) {
                v = 0xff;
            } else if (v < 0) {
                v = 0;
            }
            stats.s3 = v;
        }
        if (data_0204c240 & 2) {
            stats.s1 = stats.s1 >> 1;
        } else {
            stats.s1 = func_02005418(stats.s1, 0x666);
        }
        hdr.stat = stats.s3;
        hdr.icon = 0x2e;
        data_0204c678[member].stats = stats;
        rec->hdr = hdr;

        level = func_020235d0(0, 9);
        rewards = data_020421b8;
        for (k = 0; k < 24; k++) {
            if (level >= table->entry[k].level) {
                if (rewards.id[k] >= 1 && rewards.id[k] <= 15) {
                    int slot = rewards.id[k] - 1;
                    u8 limit = 0x63;

                    if (func_020235d0(0x35bf, 2) == 2 && rewards.id[k] >= 1 && rewards.id[k] <= 12) {
                        limit = 0;
                    }
                    aPair[0] = limit;
                    aPair[1] = aPair[0];
                    func_02035794(member, slot, (u8)table->entry[k].value, aPair);
                } else {
                    func_020358c0(member, *(volatile int *)&rewards.id[k], table->entry[k].value);
                }
            }
        }
        fixed = data_02042154;
        i = 0;
        do {
            if (i < 3) {
                aPos[0] = fixed.id[i];
            }
            aPos[1] = 0x63;
            if (func_020235d0(0x35bf, 2) != 2 || fixed.id[i] != 4) {
                func_02035830(member, aPos);
            }
            i++;
        } while (i < 3);
    }
    mover->base1c = table->base10;
    VEC_Set(&mover->pos, 0, table->base18, table->base14);
    mover->speed = 0x14000;
    func_020343cc(&table);
    func_02034258(0x1d);
}
#pragma thumb off
