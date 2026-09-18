/* func_ov245_020ccb30 -- arrival decision: `low` when the +0x21a stock is at or under half of
 * +0x218; the gap is measured against the distance from the +0x3c height (plus 15.0) to -11.0
 * (FX_Inv). While no +0x2c delay runs: a +0x38 speed under 0.25 (or under 0.5 when low) means
 * sub-state 10; a speed up to 0.75 with the ratio at or above 0.333 keeps going; otherwise a
 * 65% draw with the target's +8 height at least 5.0 away means sub-state 6, else 9. Any live
 * sub-state with the ratio at or above 0.333 becomes 6. In sub-state 6 the follow-up is chosen:
 * no +0x3fc slot busy allows 6 again, no +0x430 owner slot busy (and its +0x38c target free) and
 * a +0x420 part active allow 7, picked by a coin (the +0x43 counter takes the first two picks);
 * otherwise the sub-state is cleared to -1 and 0 returned. Returns 1 with the +0x2c delay set to
 * 0.75 (low) or 1.0. */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct Ov245Sub { char pad[0x1c7]; signed char sub; };
struct Ov245Actor { char pad[0x3fc]; int slots[9]; };
struct Ov245Owner { char pad[0x390]; int slots[10]; };
struct Ov245Parts { char pad[0x420]; int parts[3]; };

extern int FX_Inv(int num, int den);
extern int func_02023eb4(int scale);

static inline int Ov245_Abs(int x) { return x < 0 ? -x : x; }

int func_ov245_020ccb30(int *node, int gap) {
    int *state = (int *)node[1];
    int actor = *state;
    int low = *(short *)(actor + 0x200 + 0x1a) <= *(short *)(actor + 0x200 + 0x18) / 2;
    int dist;
    int speed;
    int slotsFree;
    int ownerFree;
    int coin;
    int j;
    unsigned char turn;

    dist = -0xb000 - (state[0xf] + 0xf000);
    if (dist < 0) {
        dist = -dist;
    }
    gap = FX_Inv(gap, dist);
    if (state[0xb] <= 0) {
        speed = state[0xe];
        if (speed < 0x400 || (low != 0 && speed < 0x800)) {
            *(unsigned char *)(*state + 0x1c7) = 10;
        } else if (speed > 0xc00 || gap < 0x555) {
            if ((unsigned int)func_02023eb4(0x64) < 0x41 ||
                Ov245_Abs((state[0xf] + 0xf000) - *(int *)(state[2] + 8)) < 0x5000) {
                *(unsigned char *)(*state + 0x1c7) = 9;
            } else {
                *(unsigned char *)(*state + 0x1c7) = 6;
            }
        }
    }
    if (((struct Ov245Sub *)*state)->sub != -1 && gap >= 0x555) {
        ((struct Ov245Sub *)*state)->sub = 6;
    }
    actor = *state;
    if (*(signed char *)(actor + 0x1c7) == 6) {
        slotsFree = 1;
        ownerFree = *(int *)(*(int *)(actor + 0x430) + 0x38c) == 0 ? slotsFree : 0;
        coin = (unsigned char)((unsigned int)func_02023eb4(0x64) < 0x32 ? 1 : 0);
        actor = *state;
        for (j = 0; j < 9; j++) {
            if (*(int *)(((struct Ov245Actor *)actor)->slots[j] + 0x38c) != 0) {
                slotsFree = 0;
                break;
            }
        }
        for (j = 0; j < 10; j++) {
            if (*(int *)(((struct Ov245Owner *)*(int *)(actor + 0x430))->slots[j] + 0x38c) != 0) {
                ownerFree = 0;
                break;
            }
        }
        for (j = 0; j < 3; j++) {
            if ((((struct hw60 *)(((struct Ov245Parts *)actor)->parts[j] + 0x60))->lo & 1) != 0) {
                break;
            }
        }
        turn = *((unsigned char *)state + 0x43);
        ownerFree = ownerFree & (j < 3 ? 1 : 0);
        if (turn < 2) {
            *((unsigned char *)state + 0x43) = turn + 1;
            coin = turn;
        }
        *(signed char *)(*state + 0x1c7) = -1;
        if (coin == 0) {
            if (slotsFree != 0) {
                *(unsigned char *)(*state + 0x1c7) = 6;
            }
        } else if (ownerFree != 0) {
            *(unsigned char *)(*state + 0x1c7) = 7;
        }
    }
    if (*(signed char *)(*state + 0x1c7) != -1) {
        state[0xb] = low != 0 ? 0x3000 : 0x4000;
        return 1;
    }
    return 0;
}
