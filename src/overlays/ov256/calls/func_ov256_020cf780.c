/* Claw windup tick of the ov256 actor: it re-picks its target (020ccd54); each time the partner holds
 * no queued move the windup count +0x54 grows with pose 0xb, and at 2 +0x4c clears, a charge is armed
 * (+0x69 = 1), the actor is knocked back at the origin twice (modes 0xa and 0xb), both claws (+0x434,
 * +0x438) aim at the +0x34 direction (020d108c), pose 0xc plays and the node moves on to 020cf88c. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern int func_ov256_020ccd54(int *node);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov256_020d108c(int claw, Vec3 *dir);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020cf88c(void);
extern const Vec3 data_02041dc8;

void func_ov256_020cf780(int *node)
{
    int *state = (int *)node[1];

    func_ov256_020ccd54(node);
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x15] >= 2) {
        Vec3 origin;

        state[0x13] = 0;
        *((u8 *)state + 0x69) = 1;
        origin = data_02041dc8;
        func_ov107_020c0b90(*state, 0xa, origin, 0);
        func_ov107_020c0b90(*state, 0xb, origin, 0);
        func_ov256_020d108c(*(int *)(*state + 0x434), (Vec3 *)(state + 0xd));
        func_ov256_020d108c(*(int *)(*state + 0x438), (Vec3 *)(state + 0xd));
        func_ov107_020c9264(*state, 0xc, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020cf88c);
        return;
    }
    state[0x15]++;
    func_ov107_020c9264(*state, 0xb, 0);
}
