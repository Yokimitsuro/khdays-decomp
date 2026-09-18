/* func_ov245_020ceb34 -- hit filter of the +0x214 sub-state: in sub-state 1 a hit whose low
 * flags carry bits 0 and 4 spawns effect 0 at the state's +8 position (020c0b90), fires
 * reaction 0x15a of kind 0xd there (020c5af8) and requests sub-state 0; returns 1 when handled. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int actor, int effect, Vec3 v, int flag);
extern void func_ov107_020c5af8(int actor, int a, int id, void *anchor);

int func_ov245_020ceb34(int self, int a, unsigned int *hit) {
    int *state = *(int **)(self + 0x214);
    int actor = *state;

    if (*(signed char *)(actor + 0x1c6) == 1 && ((unsigned short)*hit & 1) != 0 && ((unsigned short)*hit & 0x10) != 0) {
        func_ov107_020c0b90(actor, 0, *(Vec3 *)state[2], 0);
        func_ov107_020c5af8(*state, 0x15a, 0xd, (void *)state[2]);
        *(unsigned char *)(*state + 0x1c7) = 0;
        return 1;
    }
    return 0;
}
