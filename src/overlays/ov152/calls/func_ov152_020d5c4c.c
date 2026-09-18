/* Strafe pick of the ov151 enemy (and its byte-identical twin): turns the +8 angle into a
 * table index, reads the sin/cos pair and slews the +0x18 heading at rate 0x300. Then, unless
 * the +0x48 busy byte says otherwise, a d101 roll below 70 with any of the three +0x3c8 items
 * free (+0x60 low bit clear) requests sub-state 6, anything else sub-state 5, and the state ends.
 *
 * Load-bearing details: the y component is written BETWEEN the two table reads, the roll goes
 * through the `func_02023eb4(N) + (v - v)` copy artifact with an uninitialised scratch, the
 * free flag is a separate local set inside the loop and the declaration order i/free/items/actor
 * fixes the colouring (r2/r3/r4/ip). */
typedef struct { int x, y, z; } VecFx32;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_01ffa724(int a, void *b, void *c);
extern int func_02023eb4();
extern void func_0203c634(void *node, int idx, void *cb);
extern short data_0203d210[];

void func_ov152_020d5c4c(int *node) {
    int *state = (int *)node[1];
    VecFx32 v;
    int a;
    int roll;
    int scratch;
    int i;
    int free;
    int *items;
    int actor;

    a = (int)(unsigned short)((unsigned int)(((long long)state[2] * 0x28be60db9391LL + 0x80000000000LL) >> 32) >> 12) >> 4;
    v.x = data_0203d210[a * 2];
    v.y = 0;
    v.z = data_0203d210[a * 2 + 1];
    func_01ffa724(0x300, &v, state + 6);
    if (*(unsigned char *)state[0x12] != 0) {
        return;
    }
    roll = func_02023eb4(0x65) + (scratch - scratch);
    if (roll < 0x46) {
        actor = state[0];
        free = 0;
        items = *(int **)(actor + 0x3c8);
        for (i = 0; i < 3; i++) {
            if ((((struct hw60 *)(items[i] + 0x60))->lo & 1) == 0) {
                free = 1;
            }
        }
        if (free) {
            *(char *)(actor + 0x1c7) = 6;
        } else {
            *(char *)(actor + 0x1c7) = 5;
        }
    } else {
        *(char *)(state[0] + 0x1c7) = 5;
    }
    func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
}
