/* Applies one hit event to the actor (Ghidra: Ov215_ApplyHitEvent).
 *
 * Damage comes from the shared evaluator unless the actor is in state 5, in
 * which case a landed hit costs nothing. It is subtracted from the health at
 * +0x21a and clamped to the value at +0x218, and the attacker is recorded on
 * the node. A landed hit also plays sound 0x129, picking one of two rows of
 * takes by the event's 0x22 bits and alternating the take through the toggle
 * byte at node+0x72, so the same hit never sounds identical twice running.
 *
 * Health reaching zero writes state 3 and stops there. Otherwise a hurt or
 * guard event that arrives while the actor is in state 5 and not already
 * staggered raises the stagger counter -- to the maximum on a guard, by five
 * otherwise -- and turns the actor to face the attacker, taking the yaw from
 * the horizontal delta and reading the sine and cosine out of the shared table.
 *
 * Returns 0 when the actor is already dead or currently invulnerable.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct { int x, y, z; } VecFx32;
typedef struct { u8 a, b; } Pair2;
typedef struct { unsigned int lo : 16; unsigned int hi : 16; } EvtWord;
#define EW(e) (((EvtWord *)(e))->lo)
#define EH(e) (((EvtWord *)(e))->hi)

extern int func_ov107_020c89e8(void *self, unsigned int *evt);
extern void func_ov107_020c5af8(void *self, int id, u8 kind, void *owner);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int func_020050b4(int x, int z);
extern u8 data_ov215_020d285c[];
extern const s16 data_0203d210[];

int func_ov215_020d06f4(char *self, char *attacker, unsigned int *evt)
{
    u8 pickA[2];
    u8 pickB[2];
    VecFx32 delta;
    char **node;
    int hurt;
    int guard;
    int diff;
    int hp;
    int damage;

    node = *(char ***)(self + 0x214);
    hurt = 0;
    if (EW(evt) & 1) {
        if (EW(evt) & 0x10) {
            hurt = 1;
        }
    }
    guard = 0;
    if (EW(evt) & 8) {
        if (EH(evt) & 4) {
            guard = 1;
        }
    }
    if (*(s16 *)(self + 0x21a) <= 0) {
        return 0;
    }
    if (*(u16 *)(self + 0x1ac) & 1) {
        return 0;
    }
    if (*(char *)(*node + 0x1c6) != 5) {
        if (*(char *)(*node + 0x1c6) == 6) {
            evt[8] = 1;
        }
    } else {
        evt[8] = 0;
    }
    if (*(char *)(*node + 0x1c6) == 5) {
        damage = 0;
    } else {
        damage = func_ov107_020c89e8(self, evt);
    }
    evt[10] = damage;
    if (EW(evt) & 0x4000) {
        evt[9] = (evt[9] & ~0xffff) | 1;
        return 1;
    }
    diff = *(s16 *)(self + 0x21a) - evt[10];
    if (diff < 0) {
        hp = 0;
    } else {
        hp = *(s16 *)(self + 0x218);
        if (diff <= hp) {
            hp = diff;
        }
    }
    *(s16 *)(self + 0x21a) = (s16)hp;
    *(char **)(node + 3) = attacker;
    if ((int)evt[10] > 0) {
            if (!((EW(evt) & 8) && (EW(evt) & 0x80) && (EH(evt) == 0x80))) {
            if (EW(evt) & 0x22) {
                *(Pair2 *)pickA = *(Pair2 *)&data_ov215_020d285c[0];
                func_ov107_020c5af8(self, 0x129, pickA[*((u8 *)node + 0x72)],
                                    *(void **)(node + 4));
            } else {
                *(Pair2 *)pickB = *(Pair2 *)&data_ov215_020d285c[2];
                func_ov107_020c5af8(self, 0x129, pickB[*((u8 *)node + 0x72)],
                                    *(void **)(node + 4));
            }
            *((u8 *)node + 0x72) ^= 1;
        }
    }
    if (*(s16 *)(self + 0x21a) == 0) {
        *(char *)(*node + 0x1c7) = 3;
        return 1;
    }
    *((u8 *)node + 0x74) = 1;
    if (*(char *)(*node + 0x1c6) != 5) {
        return 1;
    }
    if ((hurt || guard) && *((u8 *)node + 0x73) == 0) {
        u8 maxStun = *((u8 *)node + 0x6f);
        u8 stun = *((u8 *)node + 0x6e);
        if (stun < maxStun) {
            if (guard) {
                *((u8 *)node + 0x6e) = maxStun;
            } else {
                *((u8 *)node + 0x6e) += 5;
                if ((u8)(stun + 5) > *((u8 *)node + 0x6f)) {
                    *((u8 *)node + 0x6e) = *((u8 *)node + 0x6f);
                }
            }
            *(int *)(node + 0x16) = 0x1fff;
            VEC_Subtract((const VecFx32 *)(attacker + 0x190),
                         (const VecFx32 *)(*node + 0xb0), &delta);
            {
                int sinv;
                int cosv;
                int idx = (u16)((int)(((long long)(func_020050b4(delta.x, delta.z) + 0xc91) * 0x28be60db9391LL + 0x80000000000LL) >> 44)) >> 4;
                sinv = data_0203d210[idx * 2];
                cosv = data_0203d210[idx * 2 + 1];
                *(int *)(node + 5) = sinv;
                *(int *)(node + 6) = 0;
                *(int *)(node + 7) = cosv;
            }
            *((u8 *)node + 0x73) = 1;
        }
    }
    return 1;
}
