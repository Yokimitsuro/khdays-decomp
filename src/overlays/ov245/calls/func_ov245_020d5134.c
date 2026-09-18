/* func_ov245_020d5134 -- clears bit 7 of the actor's +0x60 high byte; once the +4 item's
 * animation is idle (+0xad) plays pose 1, spawns effect 0 at the state's +8 position (020c0b90)
 * and moves the node to 020d51d8. */
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c0b90(int actor, int effect, Vec3 v, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020d51d8(void);

void func_ov245_020d5134(int *node) {
    int *state = (int *)node[1];

    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 1, 0);
    func_ov107_020c0b90(*state, 0, *(Vec3 *)state[2], 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d51d8);
}
