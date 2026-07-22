/* Clear the cell buffers for slots 3..6 and mark them dirty, so the next
 * Ov008_FlushDirtyCells re-uploads them. Twin of func_ov008_0204ef30,
 * which covers the other half of the seven slots.
 *
 * Parked since it was written as a "proven tie (strength reduction)": mwcc was turning the
 * per-slot address into a walking i*4 register instead of recomputing it. It is the same shape
 * as func_ov008_0204ffe4, and taking that sibling's form fixes it -- the object pointer is
 * re-read from the global INSIDE the loop into a local, the slot array is subscripted off that
 * local, and the mask byte is reached through a SECOND, separate read of the global (the
 * original loads it twice per iteration, once for the clear and once for the mask). */
extern void MIi_CpuClear16(int data, void *dest, unsigned int size);
extern int data_ov008_02090f04[];

void func_ov008_0204ef90(void) {
    int i;
    for (i = 3; i <= 6; i++) {
        char *base = (char *)data_ov008_02090f04[1];
        MIi_CpuClear16(0, ((void **)(base + 0x95a4))[i], *(int *)(base + 0x95d0) << 6);
        *(unsigned char *)((char *)data_ov008_02090f04[1] + 0x963c) |= 1 << i;
    }
}
