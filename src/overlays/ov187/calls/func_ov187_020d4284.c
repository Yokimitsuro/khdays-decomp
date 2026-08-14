typedef unsigned char u8;
typedef unsigned short u16;

struct Hw60 { u16 lo : 8; u16 hi : 8; };

struct Ov185Rig {
    char pad000[8];
    unsigned int bFlags8 : 8;
    unsigned int pad8hi : 24;
};

struct Ov185Actor {
    char pad000[0x60];
    u16 hw60;
    char pad062[0x14c];
    u16 hw1ae;
    char pad1b0[0x16];
    signed char bCurrent1c6;
    signed char bPending1c7;
    char pad1c8[0x1bc];
    void *pSubitem384;
    char pad388[0];
    struct Ov185Rig *pRig388;
};

struct Ov185ActionState {
    struct Ov185Actor *pOwner;
};

struct Ov185ActionNode {
    char pad000[4];
    struct Ov185ActionState *pState;
};

extern int data_020420f8[];

extern void func_ov187_020d4770(void);
extern void func_ov187_020d4850(void);
extern void func_ov187_020d4980(void);
extern void func_ov187_020d4b78(void);
extern void func_ov187_020d4d10(void);
extern void func_ov187_020d4e40(void);
extern void func_ov187_020d4f08(void);
extern void func_ov187_020d4fd0(void);
extern void func_ov187_020d5048(void);
extern void func_ov187_020d5388(void);

extern void func_0203c9d0(void *dst, int *src);
extern void func_0203c634(void *node, int idx, void *value);

/*
 * Starts the next action of the actor.
 *
 * Returns at once when nothing is pending.  Otherwise it raises bit 6 of the
 * actor flag byte and clears bits 1, 2, 3 and 7 of it, clears bit 0 of the
 * halfword at 0x1ae, sets bit 0 of the rig flag word, resets the subitem
 * rotation from the shared identity quaternion, latches the pending action as
 * current, and hands the node to that action's step.  Finally it marks nothing
 * pending again.
 *
 * The cases are written in the order the ten step handlers appear in the
 * overlay rather than in numeric order.  The compiler lays the case bodies out
 * in source order, so that ordering is what reproduces the ROM's jump table.
 *
 * The two flag edits need different spellings: raising bit 6 is the explicit
 * extract and reassemble, which the compiler leaves untruncated, while clearing
 * the four bits is the bitfield form that carries the halfword truncation.
 */
void func_ov187_020d4284(struct Ov185ActionNode *node)
{
    struct Ov185ActionState *state;
    u16 v;

    state = node->pState;
    if (state->pOwner->bPending1c7 == -1) {
        return;
    }
    v = state->pOwner->hw60;
    state->pOwner->hw60 = (u16)((v & ~0xff00)
                                | ((((((unsigned int)v << 0x10) >> 0x18) | 0x40)
                                    << 0x18) >> 0x10));
    ((struct Hw60 *)&state->pOwner->hw60)->hi &= ~0x8e;
    state->pOwner->hw1ae &= ~1;
    state->pOwner->pRig388->bFlags8 |= 1;
    func_0203c9d0((char *)state->pOwner->pSubitem384 + 4, data_020420f8);
    state->pOwner->bCurrent1c6 = state->pOwner->bPending1c7;
    switch (state->pOwner->bCurrent1c6) {
    case 0:
        func_0203c634(node, 1, func_ov187_020d4770);
        break;
    case 1:
        func_0203c634(node, 1, func_ov187_020d4850);
        break;
    case 2:
        func_0203c634(node, 1, func_ov187_020d4980);
        break;
    case 4:
        func_0203c634(node, 1, func_ov187_020d4b78);
        break;
    case 5:
        func_0203c634(node, 1, func_ov187_020d4d10);
        break;
    case 3:
        func_0203c634(node, 1, func_ov187_020d4e40);
        break;
    case 8:
        func_0203c634(node, 1, func_ov187_020d4f08);
        break;
    case 9:
        func_0203c634(node, 1, func_ov187_020d4fd0);
        break;
    case 6:
        func_0203c634(node, 1, func_ov187_020d5048);
        break;
    case 7:
        func_0203c634(node, 1, func_ov187_020d5388);
        break;
    }
    state->pOwner->bPending1c7 = -1;
}
