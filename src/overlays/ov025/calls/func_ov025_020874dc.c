/* func_ov025_020874dc -- build the menu grid: make sure the three resources are loaded, then walk
 * 3 pages of 40 cells, allocate a node for every populated cell and append it to the list.
 *
 * Each of the three resources (the one func_ov025_020858d0(0) names, plus 0x15 and 0x1b) is
 * loaded only if func_020342b4 says it is not already in; the flag remembered at self+0xf4/+0xe4/
 * +0xec is what decides whether this function unloads it again at the end. So the function leaves
 * the resource state exactly as it found it.
 *
 * Per cell: a zero id means an empty cell. Otherwise the cursor at self+0xf8 fills the entry
 * slot, and an entry whose +0x24 is negative is skipped too. A surviving cell gets a 0x34-byte
 * node off the default expanding heap, zeroed, and filled in:
 *   +0x00 the running 1-based counter (wrapped to a byte)
 *   +0x0a the page
 *   +0x10 / +0x12 the cell's column and row (i % 5, i / 5 -- so the grid is 5 wide, 8 tall)
 *   +0x0c / +0x0e those minus the entry's own origin at +0x28 / +0x29
 *   +0x18 / +0x1c / +0x20 left at -1
 *   +0x24 a second cursor slot, keyed 0x1b off the entry's +0x24
 *
 * `entry` walks (one word a cell) for the cursor call while `entries[i]` stays indexed for the
 * reads -- both forms are in the ROM and each is load-bearing; see codegen-cracks.md.
 *
 * ★ There is NO page-index local: `(unsigned short)page` is written straight into the node and
 * mwcc hoists the conversion out of the loop into a stack slot by itself. Introducing a local for
 * it produced seven adjacent-instruction differences that all read like irreducible scheduler
 * noise -- they were one wrong source form. */

extern void *MI_CpuFill8(void *dst, unsigned char v, unsigned int n);
extern int func_ov025_020858d0(int a);
extern int func_020342b4(int id);
extern void func_02034150(int id, int a);
extern void func_02034258(int id);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void func_ov025_02087110(int a, short *out1, short *out2);
extern void NNS_FndAppendListObject(void *list, void *obj);

void func_ov025_020874dc(int self, void **entries, void *list, unsigned short *ids) {
    /* The spilled locals go on the stack in reverse declaration order: h at sp+4, page at sp+8
     * (sp+0xc is where mwcc parks the hoisted (unsigned short)page). */
    int page;
    int h;
    int i;
    unsigned char counter;
    char *node;
    void **entry;

    counter = 1;
    MI_CpuFill8(entries, 0, 0x1e0);

    h = func_ov025_020858d0(0);
    if (func_020342b4(h) == 0) {
        func_02034150(h, 0xe);
        *(int *)(self + 0xf4) = 1;
    }
    if (func_020342b4(0x15) == 0) {
        func_02034150(0x15, 0xe);
        *(int *)(self + 0xe4) = 1;
    }
    if (func_020342b4(0x1b) == 0) {
        func_02034150(0x1b, 0xe);
        *(int *)(self + 0xec) = 1;
    }

    for (page = 0; page < 3; page++, ids += 0x28, entries += 0x28) {
        for (i = 0, entry = entries; i < 0x28; entry++, i++) {
            if (ids[i] == 0) {
                continue;
            }

            (*(void (**)(void **, int, int, int))(self + 0xf8))(entry, 0x15, ids[i], 0xe);
            if (*(int *)((char *)entries[i] + 0x24) < 0) {
                continue;
            }

            node = NNSi_FndAllocFromDefaultExpHeap(0x34);
            MI_CpuFill8(node, 0, 0x34);
            *(int *)(node + 0x20) = -1;

            (*(void (**)(void *, int, int, int))(self + 0xf8))(
                node + 0x24, 0x1b, *(int *)((char *)entries[i] + 0x24), 0xe);

            *(unsigned char *)node = counter;
            *(unsigned short *)(node + 0xa) = (unsigned short)page;
            *(unsigned short *)(node + 0x10) = i % 5;
            *(unsigned short *)(node + 0x12) = i / 5;
            *(unsigned short *)(node + 0xc) =
                *(unsigned short *)(node + 0x10) - *(unsigned char *)((char *)entries[i] + 0x28);
            *(unsigned short *)(node + 0xe) =
                *(unsigned short *)(node + 0x12) - *(unsigned char *)((char *)entries[i] + 0x29);
            *(int *)(node + 0x18) = -1;
            *(int *)(node + 0x1c) = -1;

            func_ov025_02087110(*(int *)(node + 0x24), (short *)(node + 0x14),
                                (short *)(node + 0x16));
            NNS_FndAppendListObject(list, node);
            counter++;
        }
    }

    if (*(int *)(self + 0xec) != 0) {
        func_02034258(0x1b);
        *(int *)(self + 0xec) = 0;
    }
    if (*(int *)(self + 0xe4) != 0) {
        func_02034258(0x15);
        *(int *)(self + 0xe4) = 0;
    }
    if (*(int *)(self + 0xf4) != 0) {
        func_02034258(h);
        *(int *)(self + 0xf4) = 0;
    }
}
