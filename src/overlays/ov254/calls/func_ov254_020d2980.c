/* Move entry: bit 7 of the actor's +0x60 high byte clears and bit 0 is set, the +0x388 shape is
 * armed, pose 2 plays and the node moves to 020d2a2c. */
typedef unsigned short u16;
struct Hw60 { u16 lo : 8; u16 hi : 8; };
typedef struct { unsigned f : 8; } B8;

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov254_020d2a2c(void);

void func_ov254_020d2980(int *node)
{
    int *state = (int *)node[1];

    ((struct Hw60 *)(*state + 0x60))->hi &= ~0x80;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x388) + 8))->f |= 1;
    func_ov107_020c9264(*state, 2, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d2a2c);
}
