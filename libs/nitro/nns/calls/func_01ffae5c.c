typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned long u32;
typedef signed long s32;
typedef int BOOL;

typedef struct MtxFx33 {
    s32 _00, _01, _02;
    s32 _10, _11, _12;
    s32 _20, _21, _22;
} MtxFx33;

typedef struct Rot3Entry {
    s16 packed;
    s16 first;
    s16 second;
} Rot3Entry;

typedef struct Rot5Entry {
    s16 value0;
    s16 value1;
    s16 value2;
    s16 value3;
    s16 value4;
} Rot5Entry;

typedef struct RotIndex {
    u32 value;
} RotIndex;

extern void MI_Zero36B(void *destination);
extern const u8 data_020420ac[][4];

static inline u32 Rot3Index(u32 value)
{
    return value + (value << 1);
}

BOOL func_01ffae5c(MtxFx33 *pRot, const void *pArrayRot3,
                   const void *pArrayRot5, u32 info)
{
    if (info & 0x8000) {
        u32 packed;
        const s16 *entry;
        u32 axis;
        const u8 *permutation;
        s32 second;

        MI_Zero36B(pRot);
        s32 first = Rot3Index(info & 0x7fff);
        u32 packedByteOffset = first << 1;
        packed = (u32)*(const s16 *)
            ((const u8 *)pArrayRot3 + packedByteOffset);
        entry = (const s16 *)pArrayRot3 + first;
        first = entry[1];
        second = entry[2];
        axis = packed & 0xf;
        permutation = data_020420ac[axis];
        ((s32 *)pRot)[axis] =
            (packed & 0x10) ? -0x1000 : 0x1000;
        ((s32 *)pRot)[permutation[0]] = first;
        ((s32 *)pRot)[permutation[1]] = second;
        if (entry[0] & 0x20) {
            second = -second;
        }
        ((s32 *)pRot)[permutation[2]] = second;
        if (entry[0] & 0x40) {
            first = -first;
        }
        ((s32 *)pRot)[permutation[3]] = first;
        return 0;
    } else {
        s16 value4;
        s16 value1;
        s16 value2;
        s16 value3;
        u32 value0;
        BOOL result = 1;
        u32 index = info & 0x7fff;
        u32 entryIndex = index + (index << 2);
        u32 byteOffset = entryIndex << 1;
        const Rot5Entry *entry = (const Rot5Entry *)
            ((const u8 *)pArrayRot5 + byteOffset);
        s16 packedBits;

        value4 = entry->value4;
        pRot->_11 = value4 >> 3;
        value0 = (u32)*(const s16 *)
            ((const u8 *)pArrayRot5 + byteOffset);
        pRot->_00 = (s32)value0 >> 3;
        value1 = entry->value1;
        packedBits = value4 & 7;
        packedBits = (packedBits << 3) | (value0 & 7);
        pRot->_01 = value1 >> 3;
        value2 = entry->value2;
        packedBits = (packedBits << 3) | (value1 & 7);
        pRot->_02 = value2 >> 3;
        value3 = entry->value3;
        packedBits = (packedBits << 3) | (value2 & 7);
        packedBits = (packedBits << 3) | (value3 & 7);
        pRot->_10 = value3 >> 3;
        pRot->_12 = (packedBits << 19) >> 19;
        return result;
    }
}
