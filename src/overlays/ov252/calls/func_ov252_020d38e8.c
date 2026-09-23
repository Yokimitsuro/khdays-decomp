/* Finish tick of an ov252 gem: once its +0 part stops animating (+0xad) a pending +0x3c burst plays
 * effect 1 at its +0xc point, the owner's (+4) gem mask (+0x57c) toggles its bit (+0x34 index), its
 * +0x6f8 slot clears and the node ends (0203c640). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
struct Ov252Slots { char pad[0x640]; struct { int handle; int pad; } slot[0x40]; };

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c640(int *node);

void func_ov252_020d38e8(int *node)
{
    int *state = (int *)node[1];

    if (*(u8 *)(*state + 0xad) != 0) {
        return;
    }
    if (state[0xf] != 0) {
        state[0xf] = 0;
        func_ov107_020c0b90(state[1], 1, *(Vec3 *)(state + 3), 0);
    }
    *(u16 *)(state[1] + 0x57c) ^= 1 << *((signed char *)state + 0x34);
    ((struct Ov252Slots *)state[1])->slot[*((signed char *)state + 0x34) + 0x1b].handle = 0;
    func_0203c640(node);
}
