/* Move entry: the actor's +0x38c latch is set, bit 7 of its +0x60 high byte clears and bit 0 is
 * set, the +0x388 shape is armed, pose 0 plays, the +0xc counter, the +0x20 flag and the four
 * +0x10 slots clear and the node moves to 020d26e4. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Hw60 { u16 lo : 8; u16 hi : 8; };
typedef struct { unsigned f : 8; } B8;

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov254_020d26e4(void);

void func_ov254_020d2608(int *node)
{
    int *state = (int *)node[1];
    int i;

    *(int *)(*state + 0x38c) = 1;
    ((struct Hw60 *)(*state + 0x60))->hi &= ~0x80;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x388) + 8))->f |= 1;
    func_ov107_020c9264(*state, 0, 0);
    state[3] = 0;
    *((u8 *)state + 0x20) = 0;
    for (i = 0; i < 4; i++) {
        state[4 + i] = 0;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d26e4);
}
