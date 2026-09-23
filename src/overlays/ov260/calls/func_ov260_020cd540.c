/* Move pick of the ov260 actor: with a +0x420 target and the +0x60 idle time run out, a d100 roll and
 * the flat gap to the target (distance minus both +0x80 radii) choose the next move. Move 0xa needs
 * the +0x430 part idle, move 9 the +0x42c part idle (+0x60 bit 0 clear). Grounded (+0x470 clear):
 * closer than 3.0 -> 5 (< 90) or 0xa; closer than 8.0 -> 8 (< 10), 0xa (< 75) or 9; farther -> 8
 * (< 60) or 9. Airborne: closer than 3.0 -> 5 (< 90) or 6; closer than 8.0 -> 6 (< 20), 8 (< 70), 0xa
 * (< 90) or 9; farther -> 6 (< 50), 8 (< 90) or 9. When a move was picked the idle time is rolled
 * between the +0x224 / +0x228 bounds and 1 is returned, otherwise 0. */
typedef struct { int x, y, z; } Vec3;
struct Ov260Parts { char pad[0x430]; int parts[2]; };
struct flags16 { unsigned short lo : 8; unsigned short hi : 8; };

extern int func_02023eb4(int n);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);

int func_ov260_020cd540(int *node)
{
    int *state = (int *)node[1];
    int roll;
    int partIdle;
    int shellIdle;
    int gap;
    int i;
    Vec3 d;

    if (*(int *)(*state + 0x420) == 0) {
        return 0;
    }
    if (state[0x18] <= 0) {
        roll = func_02023eb4(100);
        shellIdle = (((struct flags16 *)(*(int *)(*state + 0x42c) + 0x60))->lo & 1) == 0;
        partIdle = 1;
        for (i = 0; i < 1; i++) {
            if (((struct flags16 *)(((struct Ov260Parts *)*state)->parts[i] + 0x60))->lo & 1) {
                partIdle = 0;
                break;
            }
        }
        VEC_Subtract((Vec3 *)(*(int *)(*state + 0x420) + 0x190), (Vec3 *)state[4], &d);
        d.y = 0;
        gap = func_01ff8d18(&d, &d);
        gap -= *(int *)(*(int *)(*state + 0x420) + 0x80) + *(int *)(*state + 0x80);
        if (gap < 0) {
            gap = 0;
        }
        if (*(int *)(*state + 0x470) == 0) {
            if (gap < 0x3000) {
                if (roll < 0x5a) {
                    *(signed char *)(*state + 0x1c7) = 5;
                } else if (partIdle) {
                    *(signed char *)(*state + 0x1c7) = 0xa;
                }
            } else if (gap < 0x8000) {
                if (roll < 10) {
                    *(signed char *)(*state + 0x1c7) = 8;
                } else if (roll < 0x4b && partIdle) {
                    *(signed char *)(*state + 0x1c7) = 0xa;
                } else if (shellIdle) {
                    *(signed char *)(*state + 0x1c7) = 9;
                }
            } else {
                if (roll < 0x3c) {
                    *(signed char *)(*state + 0x1c7) = 8;
                } else if (shellIdle) {
                    *(signed char *)(*state + 0x1c7) = 9;
                }
            }
        } else {
            if (gap < 0x3000) {
                if (roll < 0x5a) {
                    *(signed char *)(*state + 0x1c7) = 5;
                } else {
                    *(signed char *)(*state + 0x1c7) = 6;
                }
            } else if (gap < 0x8000) {
                if (roll < 0x14) {
                    *(signed char *)(*state + 0x1c7) = 6;
                } else if (roll < 0x46) {
                    *(signed char *)(*state + 0x1c7) = 8;
                } else if (roll < 0x5a && partIdle) {
                    *(signed char *)(*state + 0x1c7) = 0xa;
                } else if (shellIdle) {
                    *(signed char *)(*state + 0x1c7) = 9;
                }
            } else {
                if (roll < 0x32) {
                    *(signed char *)(*state + 0x1c7) = 6;
                } else if (roll < 0x5a) {
                    *(signed char *)(*state + 0x1c7) = 8;
                } else if (shellIdle) {
                    *(signed char *)(*state + 0x1c7) = 9;
                }
            }
        }
        if (*(signed char *)(*state + 0x1c7) != -1) {
            int lo = *(int *)(*state + 0x224);
            int v = *(int *)(*state + 0x228) - lo;

            if (v < 0) {
                v = -v;
            }
            state[0x18] = lo + func_02023eb4(v + 1);
            return 1;
        }
    }
    return 0;
}
