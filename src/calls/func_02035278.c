/* Clears record `slot` of the four 0x104-byte records at data_0204c678: the 24 entry ids (+0x3c),
 * the 15 byte pairs (+0x9c) and the 5 counters (+0x28). Codegen: every loop indexes the global
 * record directly; a `rec` pointer local puts the record address in r1 instead of the ROM's r2. */
#pragma thumb on
typedef unsigned char u8;
typedef unsigned short u16;

struct SlotEntry {
    u16 nId;
    u16 nValue;
};

struct SlotPair {
    u8 a;
    u8 b;
};

struct SlotRecord {
    u8 pad00[0x28];
    int anCount[5];                 /* 0x28 */
    struct SlotEntry aEntry[24];    /* 0x3c */
    struct SlotPair aPair[15];      /* 0x9c */
    u8 padBA[0x104 - 0xba];
};

extern struct SlotRecord data_0204c678[];

void func_02035278(int slot)
{
    int i = 0;


    for (; i < 24; i++) {
        data_0204c678[slot].aEntry[i].nId = 0;
    }
    for (i = 0; i < 15; i++) {
        data_0204c678[slot].aPair[i].a = 0;
        data_0204c678[slot].aPair[i].b = 0;
    }
    for (i = 0; i < 5; i++) {
        data_0204c678[slot].anCount[i] = 0;
    }
}
