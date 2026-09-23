/* Release of the ov237 actor's grab: the actor's +0x4c4 point takes the +0x38 point, +0x58 and the
 * actor's +0x494 clear, pose 4 plays, bit 1 of the +0x488 rig's +8 flags is set and bit 6 of the
 * +0x60 high byte cleared; the release sound (0x12d variant 0xf) plays at the +0x38 point and the
 * brain waits on 020d039c. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int actor, int bank, int variant, int at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020d039c(void);

void func_ov237_020d02dc(int *node)
{
    int *state = (int *)node[1];

    *(Vec3 *)(*state + 0x4c4) = *(Vec3 *)state[0xe];
    state[0x16] = 0;
    *(int *)(*state + 0x494) = 0;
    func_ov107_020c9264(*state, 4, 0);
    ((B8 *)(*(int *)(*state + 0x488) + 8))->f |= 2;
    {
        u16 hw = *(u16 *)(state + 0x18);

        *(u16 *)(state + 0x18) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
    }
    func_ov107_020c5af8(*state, 0x12d, 0xf, state[0xe]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov237_020d039c);
}
