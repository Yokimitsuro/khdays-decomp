/* Finish tick of an ov252 marker: once its +0 part stops animating (+0xad) the owner's (+4) marker
 * mask (+0x57e) toggles the marker's bit (+0x24 index), its +0x778 slot clears and the node ends
 * (0203c640). */
typedef unsigned char u8;
typedef unsigned short u16;
struct Ov252Slots { char pad[0x640]; struct { int handle; int pad; } slot[0x40]; };

extern void func_0203c640(int *node);

void func_ov252_020d4204(int *node)
{
    int *state = (int *)node[1];

    if (*(u8 *)(*state + 0xad) != 0) {
        return;
    }
    *(u16 *)(state[1] + 0x57e) ^= 1 << *((signed char *)state + 0x24);
    ((struct Ov252Slots *)state[1])->slot[*((signed char *)state + 0x24) + 0x27].handle = 0;
    func_0203c640(node);
}
