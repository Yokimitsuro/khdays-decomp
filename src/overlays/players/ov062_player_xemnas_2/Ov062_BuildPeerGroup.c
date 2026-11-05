/*
 * Build the mission enemy's peer group: allocates the 0x60-byte group block at +0x2644, opens
 * it with one peer slot and describes that peer -- kind 0x81 (plus bit 0 when the actor's +9
 * slot evaluates packed parameter 0x30), sub-kind 1, spin 0x19a, extents 0x333 / 0x800 /
 * 0xc000 / 0x14000, no limit (0x7fffffff), the 0x333/0/0x333 triple, 4 and tag 0xa -- keyed by
 * the packed identity word built from the +0x2bd0 anchor (rounded, bits 2..23 shifted up 7)
 * and the +0x918 byte (+0xbe, 9 bits) with bit 31 set.
 *
 * THUMB. Same shape as Ov076_BuildPeerGroup: the +0x918 byte is read through a pointer local
 * declared at the top so mwcc keeps the offset in r4 across the calls (the ROM's early
 * `ldr r4,[pc]`).
 */

#include "game/engine.h"
#include "game/archive.h"

extern int NNSi_FndAllocFromDefaultExpHeap(int size);
extern void Ov022_TakeChannelBlock(int a, int b, int c);
extern void Ov022_PublishGroupUpdateFixed(int a, int b, unsigned int key, void *d);

typedef struct {
    int f00;
    int f04;
    char pad08[2];
    unsigned short f0a;
    int f0c;
    int f10;
    int f14;
    int f18;
    int f1c;
    int f20;
    int f24;
    int f28;
    int f2c;
    int f30;
    int f34;
    int f38;
    char pad3c[0x4c - 0x3c];
    unsigned char f4c;
    char pad4d[3];
} Params;

void Ov062_BuildPeerGroup(int self) {
    Params p;
    unsigned char *slot = (unsigned char *)(self + 0x918);
    *(int *)(self + 0x2644) = NNSi_FndAllocFromDefaultExpHeap(0x60);
    Ov022_TakeChannelBlock(*(int *)(self + 0x2644), 0, 1);
    p.f00 = 0x81;
    p.f04 = 1;
    p.f0a = 0x19a;
    p.f0c = 0x333;
    p.f10 = 0x800;
    p.f14 = 0xc000;
    p.f18 = 0x14000;
    p.f1c = 0;
    p.f20 = 0x7fffffff;
    p.f28 = 0;
    p.f30 = 0;
    p.f2c = 0x333;
    p.f34 = 0x333;
    p.f38 = 4;
    p.f4c = 0xa;
    if (Slot_EvalPackedParam(*(unsigned char *)(self + 9), 0x30) != 0) {
        p.f00 |= 1;
    }
    Ov022_PublishGroupUpdateFixed(*(int *)(self + 0x2644), self,
                        ARCHIVE_HANDLE(*(int *)(self + 0x2bd0), (*slot + 0xbe) & 0x1ff),
                        &p);
}
