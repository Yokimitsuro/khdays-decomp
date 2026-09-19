/* Alert approach tick of the ov266 enemy: the +0x10 velocity heads from the +0x38c item's
 * +0x40 point towards the actor's +0x5c0 goal, capped at 0x300 (a shorter gap is taken whole
 * and counts as arrived). While the +0x40 timer is under 0x3000 the +0x57c speed is the gap
 * (x4096 / 65536), afterwards it decays by 0x300 to zero. Once the speed is at most 0x200 and
 * the +4 item is idle (+0xad), bit 6 of the +0x60 flag high byte clears, the 020d0200 pass
 * runs, animation 0xb (looped) plays, the timer resets and the tick hands off to 020d1b00. */
struct Vecx32 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void func_01ffa724(int scale, void *v, void *d);
extern void func_ov266_020d0200(int *state);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov266_020d1b00(int *node);

void func_ov266_020d19b0(int *node)
{
    int *state = (int *)node[1];
    struct Vecx32 dir;
    int len;

    VEC_Subtract((void *)(*state + 0x5c0), (void *)(*(int *)(*state + 0x38c) + 0x40), &dir);
    len = func_01ff8d18(&dir, &dir);
    if (len > 0x300) {
        func_01ffa724(0x300, &dir, state + 4);
    } else {
        *(struct Vecx32 *)(state + 4) = dir;
        len = 0;
    }
    state[0x10] += *(int *)(*node + 0x2c);
    if (state[0x10] < 0x3000) {
        *(int *)(*state + 0x57c) = (len << 12) / 0x10000;
    } else {
        *(int *)(*state + 0x57c) -= 0x300;
        if (((int *)*state)[0x15f] < 0) {
            ((int *)*state)[0x15f] = 0;
        }
    }
    if (*(int *)(*state + 0x57c) > 0x200) {
        return;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x40;
    func_ov266_020d0200(state);
    func_ov107_020c9264(*state, 0xb, 1);
    state[0x10] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov266_020d1b00);
}
