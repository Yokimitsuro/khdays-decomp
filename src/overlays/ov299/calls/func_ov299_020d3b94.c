/* Spawn timer tick of the ov299 boss shell. The +8 timer accumulates frame time up to the
 * actor's +0x390 interval; then the first idle +0x384 part (its +0x38c clear) is launched by
 * d3d68 at the position of the best target among the scene's +0xa8 list: ready actors (bit 1 of
 * +0x40, bit 0 of +0x60) whose +0x1b4 kind flag bit 16 is clear, taking the first one and then
 * the closest or the farthest to the actor's +0x74 position depending on a coin toss (3eb4).
 * The timer restarts from zero. */
typedef struct Vec3 { int x, y, z; } Vec3;
struct Bits40 { int b0 : 1, b1 : 1; };
struct hw60 { unsigned short lo : 8, hi : 8; };
struct Ov299Actor { char pad000[0x384]; int parts[3]; };

extern int func_02023eb4(int range);
extern int *func_01fffd70(int list);
extern int *func_01fffd8c(int list);
extern long long *func_01fffde0(int kind);
extern void VEC_Subtract(const Vec3 *a, const void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_ov299_020d3d68(int part, int target, Vec3 *pos, int actor);
extern const Vec3 data_02041dc8;

void func_ov299_020d3b94(int *node)
{
    int *state = (int *)node[1];
    int actor = *state;
    int bestActor;
    Vec3 best;
    Vec3 d;
    Vec3 pos;
    int bestDist;
    long i;
    int pick;
    int scene;
    int *entry;
    int other;
    int len;

    if (state[2] < *(int *)(actor + 0x390)) {
        state[2] += *(int *)(*node + 0x2c);
        return;
    }
    scene = *(int *)(actor + 4);
    best = data_02041dc8;
    bestActor = 0;
    bestDist = 0x7fffffff;
    pick = func_02023eb4(2);
    for (i = 0; i < 3; i++) {
        if (*(int *)(((struct Ov299Actor *)*state)->parts[i] + 0x38c) == 0) {
            entry = func_01fffd70(scene + 0xa8);
            other = entry == 0 ? 0 : *entry;
            while (other != 0) {
                pos = *(Vec3 *)(other + 0x74);
                if (((struct Bits40 *)(other + 0x40))->b1 != 0 && (((struct hw60 *)(other + 0x60))->lo & 1) != 0 &&
                    (*func_01fffde0(*(unsigned char *)(other + 0x1b4)) & 0x10000) == 0) {
                    VEC_Subtract(&pos, (void *)(actor + 0x74), &d);
                    len = func_01ff8d18(&d, &d);
                    if (bestDist >= 0x7fffffff || (pick != 0 && len < bestDist) || (pick == 0 && len > bestDist)) {
                        bestDist = len;
                        best = *(Vec3 *)(other + 0x74);
                        bestActor = other;
                    }
                }
                entry = func_01fffd8c(scene + 0xa8);
                other = entry == 0 ? 0 : *entry;
            }
            func_ov299_020d3d68(((struct Ov299Actor *)*state)->parts[i], state[1], &best, bestActor);
            state[2] = 0;
            return;
        }
    }
}
