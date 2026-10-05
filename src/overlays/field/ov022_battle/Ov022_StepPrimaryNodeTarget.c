/* Replay step for the primary node: resolves its target pick from the recorded input, turns it
 * towards the target, and runs its hit callback, actor update and sub-object chain. */

#include "nitro/fx_types.h"

typedef struct Ov022Node {
    unsigned long long flags;
    char padding008[0x10];
    unsigned short flags018;
    unsigned short flags01a;
    char padding01c[0x4a];
    short field066;
    char padding068[0x410];
    short facing478;
    signed char mode47a;
    signed char modeData47b;
    char padding47c[0x10];
    VecFx32 position48c;
    char padding498[0x58];
    unsigned char packedLow2_4f0;
    unsigned char packedHigh_4f1;
    unsigned char packedLowShift3_4f2;
    unsigned char padding4f3;
    int packedBit2_4f4;
} Ov022Node;

typedef struct Ov022NodeOwner {
    char padding000[0x20];
    Ov022Node *node;
} Ov022NodeOwner;

typedef struct Ov022Root {
    unsigned int flags;
    char padding004[0xc];
    Ov022NodeOwner *primaryOwner;
    char padding014[0x34];
    unsigned short savedMask0;
    unsigned short savedMask1;
} Ov022Root;

extern char data_ov022_020b2e78[];
extern unsigned short gPadPressed;
extern unsigned short gPadHeld;

extern int Ov002_PollSession(void);
extern int func_ov022_02083f0c(void);
extern int Ov002_GetBit0OfField38IfValid(int p);
extern int Ov022_GetGlobalPlus14(void);
extern void Ov022_ResolveTargetPick(Ov022Node *node, int value);
extern VecFx32 *Ov002_GetWordAt0x20Plus0x20(int actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern short FX_Atan2Idx(int x, int y);
extern void func_ov022_020a0678(Ov022Node *node, int isPrimary);
extern void func_ov022_020ad474(Ov022Node *node);
extern void Ov022_RunPendingHitCallback(Ov022Node *node);
extern void Ov022_ActorUpdate(Ov022Node *node);
extern void Ov022_TickSubObjectChain(Ov022Node *node);
extern void Ov022_MarshalEntrySnapshot(int index);

void Ov022_StepPrimaryNodeTarget(int unused)
{
    VecFx32 target;
    VecFx32 delta;
    Ov022Node *node;
    Ov022Root *root = *(Ov022Root **)(data_ov022_020b2e78 + 4);
    int actor;
    int resource;

    if (root->primaryOwner == 0) {
        return;
    }
    if (Ov002_PollSession() == 0) {
        return;
    }
    node = root->primaryOwner->node;
    if (node->field066 == -1) {
        return;
    }
    actor = func_ov022_02083f0c();
    if (Ov002_GetBit0OfField38IfValid(actor) == 0) {
        return;
    }

    resource = Ov022_GetGlobalPlus14();
    node->packedLow2_4f0 =
        (unsigned int)(*(unsigned short *)(resource + 0x28) << 30) >> 30;
    node->packedHigh_4f1 = ((unsigned int)*(unsigned short *)(resource + 0x28) << 16) >> 24;
    node->packedLowShift3_4f2 =
        ((unsigned int)*(unsigned short *)(resource + 0x28) << 24) >> 27;
    node->packedBit2_4f4 = ((unsigned int)*(unsigned short *)(resource + 0x28) << 29) >> 31;
    Ov022_ResolveTargetPick(node, node->packedBit2_4f4);

    target = *Ov002_GetWordAt0x20Plus0x20(actor);
    VEC_Subtract(&target, &node->position48c, &delta);
    node->facing478 = FX_Atan2Idx(delta.x, delta.z);

    if ((node->flags & 0x1000000ULL) != 0) {
        node->flags018 &= ~0xc02;
        node->flags01a &= ~0xc02;
    }
    func_ov022_020a0678(node, 1);
    if ((root->flags & 4) == 0) {
        func_ov022_020ad474(node);
    }
    Ov022_RunPendingHitCallback(node);
    if ((root->flags & 4) == 0) {
        Ov022_ActorUpdate(node);
    }
    Ov022_TickSubObjectChain(node);
    Ov022_MarshalEntrySnapshot(1);
    root->savedMask0 = gPadPressed;
    root->savedMask1 = gPadHeld;
}

