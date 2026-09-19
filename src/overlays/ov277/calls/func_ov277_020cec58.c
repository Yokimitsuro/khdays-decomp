/* Pounce ride tick: counts the +8 timer up by the scene step; up to 0x3aaa the owner's
 * transform (+4) tracks the +0x3cc item's +0x14 point raised by 0x200 plus the actor's +0xb4
 * height. Past 0x3555 (once, latched at +0x10), if the actor's +4 target has both bits 0-1 of
 * its +0x40 set, the actor pushes pose 1. Once the owner's +0xad byte clears the node runs the
 * base 0203c640 step. */
struct Vec3 { int x, y, z; };
struct Flags40 { int b0 : 1; int b1 : 1; };
extern void func_0203ca30(int srt, struct Vec3 *pos);
extern void func_ov107_020c0b14(int self, int a);
extern void func_0203c640(int self);

void func_ov277_020cec58(int *node) {
    int *state = (int *)node[1];
    struct Vec3 at;

    state[2] += *(int *)(*node + 0x2c);
    if (state[2] <= 0x3aaa) {
        at = *(struct Vec3 *)(*(int *)(state[1] + 0x3cc) + 0x14);
        at.y = *(int *)(state[1] + 0xb4) + 0x200;
        func_0203ca30(*state + 4, &at);
    }
    if (*((unsigned char *)state + 0x10) == 0) {
        if (state[2] >= 0x3555) {
            int actor = state[1];
            *((unsigned char *)state + 0x10) = 1;
            if (*(int *)(actor + 4) != 0) {
                if (((struct Flags40 *)(*(int *)(actor + 4) + 0x40))->b0 != 0 &&
                    ((struct Flags40 *)(*(int *)(actor + 4) + 0x40))->b1 != 0) {
                    func_ov107_020c0b14(actor, 1);
                }
            }
        }
    }
    if (*(unsigned char *)(*state + 0xad) != 0) return;
    func_0203c640((int)node);
}
