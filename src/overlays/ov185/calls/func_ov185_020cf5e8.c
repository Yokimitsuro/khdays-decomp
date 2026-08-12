typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x, y, z; };
struct Hw60 { u16 lo : 8; u16 hi : 8; };

struct Ov185Rig {
    char pad000[8];
    unsigned int bFlags8 : 8;
    unsigned int pad8hi : 24;
};

struct Ov185Bone {
    char pad000[0x60];
    u16 hw60;
    char pad062[0x167];
    u8 bState1c9;
    char pad1ca[2];
    void (*pHook1cc)(struct Ov185Bone *bone, int flag);
    char pad1d0[0x114];
    int nHold2e4;
};

struct Ov185Actor {
    char pad000[0x60];
    u16 hw60;
    char pad062[0x14c];
    u16 hw1ae;
    char pad1b0[0x1d8];
    struct Ov185Rig *pRig388;
    char pad38c[4];
    struct Ov185Bone **aBones390;
};

struct Ov185ActionState {
    struct Ov185Actor *pOwner;
    char pad004[0x40];
    struct Vec3 *pAnchor44;
};

struct Ov185ActionNode {
    char pad000[4];
    struct Ov185ActionState *pState;
    char pad008[0x18];
    signed char bSlot;
};

extern const short data_0203d210[];
extern void func_ov185_020cf784(void);

extern void func_ov107_020c5c54(struct Ov185Bone *bone, struct Vec3 *pos);
extern void func_ov107_020c5af8(struct Ov185Actor *owner, int id, int mode, void *anchor);
extern void func_0203c634(void *node, int idx, void *value);

/*
 * Opens the ring-burst action.
 *
 * Sets the actor's ring flags, clears the pose gate, then places the four bone
 * attachments evenly around the anchor: every idle bone is picked up, given
 * state 5, told through its hook, and moved to the anchor offset by the sin and
 * cos of its share of the circle, with a hold timer of 0x800.  Finally the ring
 * event is raised and the node is handed to the follow-up action.
 *
 * The running angle is in fixed-point radians, so the table index is the angle
 * times one over two pi, done as a 48-bit multiply.  The accumulator is
 * unsigned and the quarter is taken through a signed reinterpretation: with a
 * plain signed accumulator the compiler proves it never goes negative and drops
 * the rounding out of the division entirely.
 *
 * The index variable holds the already doubled entry number rather than the
 * entry itself.  The table is an array of shorts read in pairs, so doubling at
 * the point of use instead would let the compiler fold both scalings into one
 * shift; keeping the doubled value is what produces the two chained shifts the
 * ROM has, and it also keeps the two pool constants hoisted out of the loop.
 */
void func_ov185_020cf5e8(struct Ov185ActionNode *node)
{
    struct Vec3 vPos;
    struct Ov185ActionState *state;
    int i;
    struct Ov185Bone *bone;
    unsigned int nAngle;
    int nQuarter;
    long nIndex;
    u16 v;

    state = node->pState;
    i = 0;
    v = state->pOwner->hw60;
    state->pOwner->hw60 = (u16)((v & ~0xff00)
                                | ((((((unsigned int)v << 0x10) >> 0x18) | 0x86)
                                    << 0x18) >> 0x10));
    nAngle = 0;
    state->pOwner->hw1ae |= 1;
    state->pOwner->pRig388->bFlags8 &= ~1;
    do {
        bone = state->pOwner->aBones390[i];
        if ((((struct Hw60 *)&bone->hw60)->lo & 1) == 0) {
            bone->bState1c9 = 5;
            if (bone->pHook1cc != 0) {
                bone->pHook1cc(bone, 0);
            }
            nQuarter = (int)nAngle / 4;
            nIndex = ((u16)((nQuarter * 0x28BE60DB9391LL + 0x80000000000LL) >> 44) >> 4) * 2;
            vPos = *state->pAnchor44;
            vPos.x += data_0203d210[nIndex];
            vPos.z += data_0203d210[nIndex + 1];
            func_ov107_020c5c54(bone, &vPos);
            bone->nHold2e4 = 0x800;
        }
        nAngle += 0x6488;
    } while (++i < 4);
    func_ov107_020c5af8(state->pOwner, 0x120, 6, state->pAnchor44);
    func_0203c634(node, node->bSlot, func_ov185_020cf784);
}
