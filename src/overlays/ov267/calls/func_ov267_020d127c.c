/* Grab-phase machine of the ov266 enemy on its +0x6c phase: 0 and 1 consume a pending request
 * (+0x70, -1 when none) and advance to phase 2 / 4 when it asks so; 2 plays animation 1, fires
 * reaction 0x15e mode 6 at the +8 point and enters 3; 3 waits for the +4 item (+0xaf), then sets
 * bit 1 of the +0x4cc target's +8 word and bit 4 of +0x1ae and enters 1; 4 plays animation 2,
 * fires mode 7, clears those two bits and enters 5; 5 waits for the item and plays animation 0
 * back to phase 0. */
typedef unsigned int u32;
struct w8 { u32 lo : 8, rest : 24; };

extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov107_020c5af8(int actor, int a, int b, void *at);

void func_ov267_020d127c(int *state)
{
    switch (state[0x1b]) {
    case 0:
        if (state[0x1c] == -1) {
            return;
        }
        if (state[0x1c] == 2) {
            state[0x1b] = state[0x1c];
        }
        state[0x1c] = -1;
        return;
    case 1:
        if (state[0x1c] == -1) {
            return;
        }
        if (state[0x1c] == 4) {
            state[0x1b] = state[0x1c];
        }
        state[0x1c] = -1;
        return;
    case 2:
        func_ov107_020c9264(*state, 1, 0);
        func_ov107_020c5af8(*state, 0x15e, 6, (void *)state[2]);
        state[0x1b] = 3;
        return;
    case 3:
        if (*(unsigned char *)(state[1] + 0xaf) != 0) {
            return;
        }
        ((struct w8 *)(*(int *)(*state + 0x4cc) + 8))->lo |= 2;
        *(unsigned short *)(*state + 0x100 + 0xae) |= 0x10;
        state[0x1b] = 1;
        return;
    case 4:
        func_ov107_020c9264(*state, 2, 0);
        func_ov107_020c5af8(*state, 0x15e, 7, (void *)state[2]);
        ((struct w8 *)(*(int *)(*state + 0x4cc) + 8))->lo &= ~2;
        *(unsigned short *)(*state + 0x100 + 0xae) &= ~0x10;
        state[0x1b] = 5;
        return;
    case 5:
        if (*(unsigned char *)(state[1] + 0xaf) != 0) {
            return;
        }
        func_ov107_020c9264(*state, 0, 0);
        state[0x1b] = 0;
        return;
    }
}
