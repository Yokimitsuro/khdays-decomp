/* func_ov245_020d6d78 -- launch tick: takes the +0x3a0 item's forward vector (020c9f48, speed
 * returned), rotates it by the actor's +0xa0 placement into the state's +0x1c direction and
 * scales it by the speed; once the +4 item's animation is no longer busy (+0xad) the direction
 * is copied to +0x28 and the node moves to 020d6e00. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020c9f48(int item, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020d6e00(void);

void func_ov245_020d6d78(int *node) {
    int *state = (int *)node[1];
    Vec3 fwd;
    int speed;

    speed = func_ov107_020c9f48(*(int *)(*state + 0x3a0), &fwd);
    func_0202f384((Vec3 *)(state + 7), (void *)(*state + 0xa0), &fwd);
    func_01ffa724(speed, (Vec3 *)(state + 7), (Vec3 *)(state + 7));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(Vec3 *)(state + 10) = *(Vec3 *)(state + 7);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d6e00);
}
