typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

/* STRANGE, AND LIKELY NOT HOW THE ORIGINAL WAS WRITTEN. Kept by owner decision
 * (2026-09-12) because it is the only form found that matches.
 * The two copy loops below write each halfword into this union as signed and
 * read it back as unsigned. The value never changes; the round-trip's only
 * effect is the brief halfword store to the stack that the ROM performs. It is
 * the same kind of type pun as the rejected one-word struct copy cast. Replace
 * it when a plain form that reproduces the stack store is found. */
typedef union {
    s16 value;
    u16 raw;
} SignedHalfword;

typedef struct {
    u16 field_00;
    u16 field_02;
    u16 field_04;
} SourceRow;

typedef struct {
    u16 field_00;
    u16 field_02;
    SourceRow rows[8];
    u16 values_34[8];
    u16 values_44[14];
    u8 tail[0x1c];
} SourceFile;

typedef struct {
    u16 field_04;
    unsigned char flags0_06 : 2;
    unsigned char flags2_06 : 4;
    unsigned char flags6_06 : 1;
    unsigned char flags7_06 : 1;
    u8 field_07;
} OutputRow;

typedef struct {
    unsigned char flag0 : 1;
    unsigned char flag1 : 1;
    unsigned char flag2 : 1;
    unsigned char flag3 : 1;
    unsigned char reserved : 4;
} OutputFlags;

typedef struct {
    u16 field_00;
    u16 field_02;
    OutputRow rows[8];
    s16 values_24[8];
    s16 values_34[14];
    u8 field_50;
    u8 field_51;
    u8 field_52;
    u8 field_53;
    u16 field_54;
    u16 field_56;
    u16 field_58;
    u16 field_5a;
    OutputFlags flags_5c;
    u8 field_5d;
    u16 field_5e;
    u16 field_60;
    u16 field_62;
    u16 field_64;
    u16 field_66;
    u16 field_68;
} Output;

typedef struct {
    u8 pad_00[0x7c];
    u32 field_7c;
} Manager;

extern Manager *OS_IsThreadAvailable_0x020c9848(void);
extern void *func_0201ef9c(u32 resource, int kind);
extern void NNSi_FndFreeFromDefaultHeap(void *user_ptr);

/* Load one actor configuration and expand its packed fields into the shared slot. */
int func_ov107_020c2f94(int id, Output *slot)
{
    Manager *manager;
    SourceFile *source;
    u32 mask;
    int i;
    SourceRow *sourceRow;
    int packedFlags;
    u16 *sourceValues;
    u8 *sourceTail;
    int sourceFlags;
    SignedHalfword arrayValue;
    SignedHalfword tailValue;

    manager = OS_IsThreadAvailable_0x020c9848();
    mask = 0xfffffc;
    source = (SourceFile *)func_0201ef9c(
        ((((manager->field_7c + 0x8000) & mask) << 7) | 0x80000000)
            | (id & (mask >> 15)), 0xb);

    slot->field_00 = source->field_00;
    sourceRow = source->rows;
    slot->field_02 = source->field_02;

    for (i = 0; i < 8; i++) {
        slot->rows[i].field_04 = sourceRow->field_00;
        packedFlags = (u8)sourceRow->field_02;
        slot->rows[i].flags0_06 = (packedFlags >> 4) & 3;
        slot->rows[i].flags2_06 = packedFlags & 0xf;
        slot->rows[i].flags6_06 = (packedFlags >> 6) & 1;
        slot->rows[i].flags7_06 = (packedFlags >> 7) & 1;
        slot->rows[i].field_07 = (u8)sourceRow->field_04;
        sourceRow++;
    }

    sourceValues = (u16 *)sourceRow;
    /* Suspect: see SignedHalfword. The union round-trip is a no-op on the value
     * and exists only because it reproduces the ROM's stack store. */
    for (i = 0; i < 8; i++) {
        arrayValue.value = (s16)*sourceValues++;
        slot->values_24[i] = arrayValue.raw;
    }
    for (i = 0; i < 14; i++) {
        tailValue.value = (s16)*sourceValues++;
        slot->values_34[i] = tailValue.raw;
    }

    sourceTail = (u8 *)sourceValues;
    slot->field_51 = sourceTail[0];
    slot->field_52 = sourceTail[1];
    slot->field_53 = sourceTail[2];
    slot->field_54 = *(u16 *)&sourceTail[4];
    slot->field_56 = *(u16 *)&sourceTail[6];
    slot->field_58 = *(u16 *)&sourceTail[8];
    slot->field_5a = *(u16 *)&sourceTail[10];
    sourceFlags = sourceTail[12];
    slot->flags_5c.flag0 = sourceFlags & 1;
    slot->flags_5c.flag1 = (sourceFlags >> 1) & 1;
    slot->flags_5c.flag2 = (sourceFlags >> 2) & 1;
    slot->flags_5c.flag3 = (sourceFlags >> 3) & 1;
    slot->field_5d = sourceTail[13];
    slot->field_5e = *(u16 *)&sourceTail[14];
    slot->field_60 = *(u16 *)&sourceTail[16];
    slot->field_62 = *(u16 *)&sourceTail[18];
    slot->field_50 = sourceTail[20];
    slot->field_64 = *(u16 *)&sourceTail[22];
    slot->field_66 = *(u16 *)&sourceTail[24];
    slot->field_68 = *(u16 *)&sourceTail[26];

    NNSi_FndFreeFromDefaultHeap(source);
    return 1;
}
