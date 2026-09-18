/* Attack entry of the ov219 enemy: plays animation 6, starts sub-animation 0, fires reaction
 * 0x136 mode 6 at the +8 position; coming from sub-state 3 with the +0x21a stamina spent the
 * +0x388 item's +8 byte gets bit 1, and with a +0x40 target the +0xc/+0x10 yaw turns towards it
 * (from the actor's +0xb0 point to the target's +0x190 point). The target is cleared and the
 * tick hands off to the attack tick. */
typedef unsigned char u8;
typedef short s16;
struct Vecx32 { int x, y, z; };
struct b8 { unsigned f : 8; };

extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov219_020d05dc(int actor, int anim);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_020050b4(int x, int z);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov219_020d134c(int *node);

void func_ov219_020d1268(int *node)
{
    int *state = (int *)node[1];
    struct Vecx32 dir;
    int actor;

    func_ov107_020c9264(*state, 6, 0);
    func_ov219_020d05dc(*state, 0);
    func_ov107_020c5af8(*state, 0x136, 6, (void *)state[2]);
    actor = *state;
    if (*(signed char *)(actor + 0x1c6) == 3) {
        if (*(s16 *)(actor + 0x21a) == 0) {
            ((struct b8 *)(*(int *)(actor + 0x388) + 8))->f |= 2;
        }
        if (state[0x10] != 0) {
            VEC_Subtract((void *)(state[0x10] + 0x190), (void *)(*state + 0xb0), &dir);
            state[3] = state[4] = func_020050b4(dir.x, dir.z);
        }
    }
    state[0x10] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov219_020d134c);
}
