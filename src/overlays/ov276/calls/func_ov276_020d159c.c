/* Idle tick of the ov276 enemy: the +0x4c clock accumulates the frame-time; with the +4 item's
 * +0xad byte set, no queued +0x60 sub-state and less than 0x1000 elapsed nothing happens.
 * Otherwise the actor's +0x3bc target is re-acquired: with one, the gap between the +0xc
 * position and its +0x190 point beyond the +0x480 and +0x80 radii is measured; while the
 * +0x54 timer is spent the idle countdown may end the state, and unless the mission mode is 2
 * the clock resets (animation 1 when the item's +0xad byte is clear). Else the +0x5c attack
 * choice is 1 (gap below 0x1000, 45% roll), 2 or 3 at random (gap below 0x3000, unless already
 * one of them) or 0, sub-state 4 is requested and the state ends. */
struct Vecx32 { int x, y, z; };

extern int func_ov107_020cab14(int actor, int mode);
extern void VEC_Subtract(void *a, void *b, struct Vecx32 *d);
extern int func_01ff8d18(struct Vecx32 *v, struct Vecx32 *d);
extern int func_ov276_020d0be8(int *node, int dist);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_ov002_0207298c(void);
extern int func_02023eb4(int range);
extern void func_ov107_020c9264(int actor, int anim, int flag);

void func_ov276_020d159c(int *node)
{
    int *state = (int *)node[1];
    struct Vecx32 d;
    int gap;
    int len;
    int actor;

    state[0x13] += *(int *)(*node + 0x2c);
    if (*(unsigned char *)(state[1] + 0xad) != 0 && *(signed char *)(state + 0x18) == -1 && state[0x13] < 0x1000) {
        return;
    }
    *(int *)(*state + 0x3bc) = func_ov107_020cab14(*state, 0);
    if (*(int *)(*state + 0x3bc) != 0) {
        VEC_Subtract((void *)(*(int *)(*state + 0x3bc) + 0x190), (void *)state[3], &d);
        len = func_01ff8d18(&d, &d);
        actor = *state;
        gap = len - (*(int *)(actor + 0x480) + *(int *)(*(int *)(actor + 0x3bc) + 0x80));
        if (state[0x15] <= 0) {
            if (func_ov276_020d0be8(node, gap) != 0) {
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            if (func_ov002_0207298c() != 2) {
                goto reset;
            }
        }
        if (gap < 0x1000 && (unsigned int)func_02023eb4(0x64) < 0x2d) {
            state[0x17] = 1;
        } else if (gap < 0x3000) {
            if (state[0x17] != 2 && state[0x17] != 3) {
                state[0x17] = func_02023eb4(2) != 0 ? 2 : 3;
            }
        } else {
            state[0x17] = 0;
        }
        *(unsigned char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
reset:
    state[0x13] = 0;
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 1, 0);
    }
}
