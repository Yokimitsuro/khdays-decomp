/*
 * func_ov121_020cf11c -- Ov121_AreaAttack_Broadcast.
 *
 * One frame of the area attack that follows the charge. Shared byte-for-byte with ov120 and
 * ov122; against ov120 only the two message globals differ.
 *
 * The scene delta accumulates in the action state. Once past 0x555 the actor's message hook
 * receives a four-byte opening packet exactly once, guarded by a one-shot byte. From then on
 * every frame sweeps the entities within 0x300 of the attack body and, for each one whose id bit
 * is not yet set in the state's mask, aims at it: owner to entity, flattened onto the ground
 * plane, normalised, falling back to the forward constant when the aim degenerates, then scaled
 * by 0x800. The ov107 checker decides whether the hit lands; on acceptance the fourteen-byte
 * template is patched with the attack body's position packed as three sign-plus-magnitude 24-bit
 * components, broadcast through the same hook, the id bit is set and reaction 0x4e fires.
 *
 * Finally the target is re-acquired and the action ends when there is none, or when the byte the
 * state's gate pointer refers to has gone to zero.
 *
 * Ghidra: Ov121_AreaAttack_Broadcast(Ov120ActionNode *pNode), types /khdays/Ov120ActionNode,
 * /khdays/Ov120ActionState, /khdays/Ov120Actor, /khdays/Ov120AttachBody,
 * /khdays/Ov107SweepEntity, /khdays/Ov107SweepQuery, /khdays/Ov120AreaMsgPair,
 * /khdays/Ov120AreaMsg, /khdays/SceneFrameClock and /khdays/Vec3.
 *
 * Byte-exact codegen notes (mwccarm 3.0/139):
 *  - THE OPENER AND THE TEMPLATE ARE ONE 18-BYTE STACK OBJECT, matching their two globals at
 *    020cfd10 and 020cfd14. Declared as two separate locals the four-byte opener lands at sp+8
 *    instead of sp+0x14, because mwcc orders the frame by alignment and not by declaration.
 *  - The two template copies are in the loop PREHEADER, not inside the loop: mwcc does not hoist
 *    a struct copy out of a loop body, so the guard has to be written explicitly as
 *    `if (count > 0) { copies; do { ... } while (++i < count); }`. Written as a plain `for` with
 *    the copies inside, the whole copy runs every iteration and the back edge jumps over it.
 *  - `i = 0` sits before the guard so mwcc can schedule it between the compare and the branch,
 *    exactly where the original puts it.
 *  - Each of the three uses of the swept entity re-reads `aResults[i]`; the intervening calls
 *    stop mwcc reusing one load, and caching it in a local costs an instruction.
 *  - The mask update takes no byte cast: `(u8)(1 << id)` adds an `and #0xff`.
 *  - The body position is also written to a twelve-byte stack copy nothing ever reads, one word
 *    at a time through a one-word struct -- the ov149 crack, so the store survives dead-store
 *    elimination and fuses with the packing.
 */
typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x, y, z; };
struct Word { int w; };
struct Ov120AreaMsg { u16 h[7]; };
struct Ov120AreaOpener { u16 h[2]; };
struct Ov120AreaMsgPair { struct Ov120AreaOpener aOpener; struct Ov120AreaMsg aTemplate; };
struct Ov107SweepQuery { struct Vec3 vPos; int nRadius; };

struct Ov120Actor {
    char pad000[0x24];
    void (*pMsgHook24)(struct Ov120Actor *actor, void *msg, int len);
    char pad028[0x19f];
    u8 bActionState1c7;
    char pad1c8[0x1c8];
    int *pBody390;
};

struct Ov120ActionState {
    struct Ov120Actor *pOwner;
    char pad004[4];
    void *pTarget;
    void *pEventAnchor;
    char pad010[0x30];
    int nElapsed40;
    char pad044[4];
    u8 *pGate48;
    char pad04c[0];
    u8 bOneShot4c;
    u8 bHitMask4d;
};

struct SceneFrameClock {
    char pad00[0x2c];
    int nDelta2c;
};

struct Ov120ActionNode {
    struct SceneFrameClock *pClock;
    struct Ov120ActionState *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern struct Ov120AreaOpener data_ov121_020cfd10;
extern struct Vec3 data_02042258;
extern struct Ov120AreaMsg data_ov121_020cfd14;

extern int func_ov107_020c8eb8(struct Ov120Actor *owner, void *query, void *results);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_01ff8d18(struct Vec3 *v, struct Vec3 *unit);
extern void func_01ffa724(int scale, void *src, void *dst);
extern int func_ov107_020ca918(int ent, struct Ov120Actor *a, struct Ov120Actor *b, int mode,
                               void *dir, int flag);
extern void func_ov107_020c5af8(struct Ov120Actor *owner, int a, int id, void *anchor);
extern void *func_ov107_020cab14(struct Ov120Actor *owner, int out);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov121_020cf11c(struct Ov120ActionNode *node)
{
    int results[4];
    struct Ov107SweepQuery query;
    struct Vec3 dir;
    struct Ov120AreaMsg msg;
    struct Vec3 fwd;
    struct Ov120AreaMsgPair pair;
    struct Vec3 vDead;
    struct Ov120ActionState *state;
    struct Word *s;
    int count;
    int i;

    state = node->pState;
    state->nElapsed40 += node->pClock->nDelta2c;
    if (state->bOneShot4c == 0 && state->nElapsed40 >= 0x555) {
        pair.aOpener = data_ov121_020cfd10;
        if (state->pOwner->pMsgHook24 != 0) {
            state->pOwner->pMsgHook24(state->pOwner, &pair.aOpener, 4);
        }
        state->bOneShot4c = 1;
    }
    if (state->nElapsed40 >= 0x555) {
        query.vPos = *(struct Vec3 *)(state->pOwner->pBody390 + 5);
        query.nRadius = 0x300;
        count = func_ov107_020c8eb8(state->pOwner, &query, results);
        i = 0;
        if (count > 0) {
            fwd = data_02042258;
            pair.aTemplate = data_ov121_020cfd14;
            do {
                if ((state->bHitMask4d & (1 << *(u16 *)(results[i] + 2))) == 0) {
                    VEC_Subtract((void *)(results[i] + 0x74), state->pEventAnchor, &dir);
                    dir.y = 0;
                    if (func_01ff8d18(&dir, &dir) == 0) {
                        dir = fwd;
                    }
                    func_01ffa724(0x800, &dir, &dir);
                    if (func_ov107_020ca918(results[i], state->pOwner, state->pOwner, 0, &dir, 0) != 0) {
                        msg = pair.aTemplate;
                        s = (struct Word *)(state->pOwner->pBody390 + 5);

                        *(struct Word *)&vDead.x = s[0];
                        ((u8 *)&msg)[5] = (u8)(((unsigned int)vDead.x >> 0x10 & 0x7f)
                                               | ((unsigned int)vDead.x >> 0x18 & 0x80));
                        ((u8 *)&msg)[6] = (u8)((unsigned int)vDead.x >> 8);
                        ((u8 *)&msg)[7] = (u8)vDead.x;

                        *(struct Word *)&vDead.y = s[1];
                        ((u8 *)&msg)[8] = (u8)(((unsigned int)vDead.y >> 0x10 & 0x7f)
                                               | ((unsigned int)vDead.y >> 0x18 & 0x80));
                        ((u8 *)&msg)[9] = (u8)((unsigned int)vDead.y >> 8);
                        ((u8 *)&msg)[10] = (u8)vDead.y;

                        *(struct Word *)&vDead.z = s[2];
                        ((u8 *)&msg)[11] = (u8)(((unsigned int)vDead.z >> 0x10 & 0x7f)
                                                | ((unsigned int)vDead.z >> 0x18 & 0x80));
                        ((u8 *)&msg)[12] = (u8)((unsigned int)vDead.z >> 8);
                        ((u8 *)&msg)[13] = (u8)vDead.z;

                        if (state->pOwner->pMsgHook24 != 0) {
                            state->pOwner->pMsgHook24(state->pOwner, &msg, 0xe);
                        }
                        state->bHitMask4d |= 1 << *(u16 *)(results[i] + 2);
                        func_ov107_020c5af8(state->pOwner, 0, 0x4e,
                                            state->pOwner->pBody390 + 5);
                    }
                }
            } while (++i < count);
        }
    }
    state->pTarget = func_ov107_020cab14(state->pOwner, 0);
    if (state->pTarget == 0) {
        state->pOwner->bActionState1c7 = 2;
        func_0203c634(node, node->bSlot, 0);
        return;
    }
    if (*state->pGate48 == 0) {
        state->pOwner->bActionState1c7 = 2;
        func_0203c634(node, node->bSlot, 0);
    }
}
