/* Land tick of the ov237 actor: the +0x3c aim point resets to data_ov237_020d1be8; once the +4 rig
 * is idle (or the +0x17a bit 3 lands early) the actor is placed at its +0x4c4 point at the +0x38
 * point's height with effect 0x12, +0x4bc is set, pose 0x10 plays and the brain waits on 020d06e0. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 1; } Bits;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5c54(int owner, const Vec3 *pos);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020d06e0(void);
extern const Vec3 data_ov237_020d1be8;

void func_ov237_020d05d0(int *node)
{
    int *state = (int *)node[1];
    Vec3 pos;

    *(Vec3 *)(state + 0xf) = data_ov237_020d1be8;
    if (*(u8 *)(state[1] + 0xad) != 0 && !((Bits *)(*state + 0x17a))->b3) {
        return;
    }
    if (*(int *)(*state + 0x4ac) != 0) {
        pos = *(Vec3 *)(*state + 0x4c4);
        pos.y = ((Vec3 *)state[0xe])->y;
    } else if (*(int *)(*state + 0x4ac) == 0) {
        pos = *(Vec3 *)(*state + 0x4c4);
        pos.y = ((Vec3 *)state[0xe])->y;
    }
    func_ov107_020c0b90(*state, 0x12, *(Vec3 *)state[0xe], 0);
    func_ov107_020c5c54(*state, &pos);
    *(int *)(*state + 0x4bc) = 1;
    func_ov107_020c9264(*state, 0x10, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov237_020d06e0);
}
