/* Approach tick of the ov261 enemy (and its byte-identical twin): the +0x30 velocity heads on
 * the ground plane towards the +0x2c point of the +0x49 grab slot (capped at 0x100), the +0x3c
 * rate is the frame-time (30/30) and the +0x34 lift eases by a fiftieth towards 0x2000 above the
 * +0x13c height. When the +0x3a8 part's +4 owner matches the actor's, bit 7 of the +0x60 flag
 * high byte clears, animation 0 (looped) plays, the +0x6c index resets and the tick hands off to
 * the grab walk. */
typedef unsigned char u8;
struct Vecx32 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void func_01ffa724(int scale, void *v, void *d);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov262_020d4bd0(int *node);

void func_ov262_020d4a8c(int *node)
{
    int *state = (int *)node[1];
    struct Vecx32 goal;
    struct Vecx32 dir;
    int len;
    int speed;
    int d;
    int actor;

    goal = *(struct Vecx32 *)(*(int *)(*state + 0x3a0) + *(u8 *)((char *)state + 0x49) * 0x24 + 0x2c);
    VEC_Subtract(&goal, (void *)state[1], &dir);
    dir.y = 0;
    len = func_01ff8d18(&dir, &dir);
    speed = 0x100;
    if (len < 0x100) {
        speed = len;
    }
    func_01ffa724(speed, &dir, state + 0xc);
    state[0xf] = *(int *)(*node + 0x2c) * 30 / 30;
    d = 0x2000 - *(int *)(*state + 0x13c);
    state[0xd] += d / 50;
    actor = *state;
    if (*(int *)(*(int *)(actor + 0x3a8) + 4) == *(int *)(actor + 4)) {
        ((struct hw60 *)(actor + 0x60))->hi &= ~0x80;
        func_ov107_020c9264(*state, 0, 1);
        state[0x1b] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov262_020d4bd0);
    }
}
