/*
 * File a freshly built task node in its registry slot.
 *
 * The registry holds two banks of 32 slots, 0x120 bytes apart: bit 0x1000 of the slot id picks
 * the second bank and is then masked out of the index. Each bank keeps its node pointers at the
 * front and the matching status bytes at +0x100; bit 0 of a status byte means the slot is closed,
 * and a node offered to a closed slot is simply dropped. Storing a node also stamps -1 into its
 * byte at +0x11, which is how a node marks itself as registered.
 *
 * Ghidra carries the layout as Ov002TaskNodeBank and Ov002TaskRegistry.
 */

typedef unsigned char u8;
typedef unsigned int u32;

extern u8 *data_ov002_0207fa04;

void func_ov002_0206edf0(u32 slot, void *node) {
    u8 *registry = data_ov002_0207fa04;
    u8 *bank;

    if ((slot & 0x1000) != 0) {
        bank = registry + 300;
        slot &= ~0x1000;
    } else {
        bank = registry + 0xc;
    }
    if (((*(bank + slot + 0x100) & 1) == 0) > 0) {
        *(void **)(bank + slot * 4) = node;
        *((char *)*(void **)(bank + slot * 4) + 0x11) = -1;
    }
}
