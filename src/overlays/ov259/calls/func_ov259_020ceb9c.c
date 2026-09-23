/* Rising tick of the ov259 actor: the +0x68 and +0x6c clocks run up at the frame rate, the ground
 * height is measured (020cdc20), the facing updated (020cdcac) and the +0x14 velocity damped to 0.45.
 * Back on the floor (the owner's +0x80) the +0xae phase becomes 11, the clocks and +0x98 / +0x80 reset
 * and 020ced2c runs next. After 3.0, or while the +8 target is higher than the owner by more than two
 * floors and airborne, the owner switches to move 12 (+0xad latched). Otherwise the two wing flaps
 * fire once each at 0.23 and 0.56 (020cd2c8, +0xac bits 0/1) and, once the +4 rig is idle, pose 1
 * and rig motion 1 restart the flap cycle. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
struct b1 { unsigned char b0 : 1; };

extern int func_ov259_020cdc20(int *node);
extern int func_ov259_020cdcac(int *node);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020cd2c8(int actor, int flag);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c9ee8(int rig, int motion, int mode);
extern void func_ov259_020ced2c(void);

void func_ov259_020ceb9c(int *node)
{
    int *state = (int *)node[1];
    int ground;
    int owner;
    int floor;

    state[0x1a] += *(int *)(node[0] + 0x2c);
    state[0x1b] += *(int *)(node[0] + 0x2c);
    ground = func_ov259_020cdc20(node);
    func_ov259_020cdcac(node);
    func_01ffa724(0x1d00, (Vec3 *)(state + 5), (Vec3 *)(state + 5));
    owner = *state;
    floor = *(int *)(owner + 0x80);
    if (ground <= floor) {
        *((u8 *)state + 0xae) = 0xb;
        state[0x1c] = 0;
        state[0x1a] = 0;
        state[0x26] = 0;
        state[0x20] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020ced2c);
        return;
    }
    if (state[0x1a] > 0x3000 ||
        (*(int *)(state[2] + 0xb4) > *(int *)(owner + 0xb4) + floor * 2 &&
         ((struct b1 *)(state[2] + 0x17a))->b0 == 0)) {
        *((u8 *)state + 0xad) = 0xc;
        *(signed char *)(*state + 0x1c7) = 0xc;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if ((*((u8 *)state + 0xac) & 1) == 0 && state[0x1b] >= 0x3b8) {
        *((u8 *)state + 0xac) |= 1;
        func_ov259_020cd2c8(*state, 0);
    }
    if ((*((u8 *)state + 0xac) & 2) == 0 && state[0x1b] >= 0x908) {
        *((u8 *)state + 0xac) |= 2;
        func_ov259_020cd2c8(*state, 1);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 1, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x414), 1, 0);
    state[0x1b] = 0;
    *((u8 *)state + 0xac) = 0;
}
