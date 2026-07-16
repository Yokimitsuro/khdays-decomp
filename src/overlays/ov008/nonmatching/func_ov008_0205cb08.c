/* NONMATCHING: semantics correct; ties on constant-multiply strategy — the ROM computes the
 * cell address with runtime MLA (strides 0x28/0xc8 in registers), mwcc expands *0x28 and *200
 * into shift-adds (+12B). Not steerable from C. */
/* func_ov008_0205cb08 -- ov008: clear all pending grid-cell markers and free their list nodes.
 * Walks the object list at obj+0x19b8; for each node writes 0x1f into the map cell at
 * (obj.col+node[4])*0x28 + (obj.row+node[8])*200 + obj+0x10be, unlinks and frees the node, and
 * zeroes the per-row field at obj+0x184c (advancing 0x28 per row). */
extern int  NNS_FndGetNextListObject(void *list, int obj);
extern void NNS_FndRemoveListObject(void *list, int obj);
extern void NNSi_FndFreeFromDefaultHeap(int p);

void func_ov008_0205cb08(int param_1) {
    int node = NNS_FndGetNextListObject((void *)(param_1 + 0x19b8), 0);
    int row = param_1;
    int next;
    if (node != 0) {
        do {
            next = NNS_FndGetNextListObject((void *)(param_1 + 0x19b8), node);
            *(unsigned short *)(((unsigned int)*(unsigned short *)(param_1 + 0x6c) + *(int *)(node + 4)) * 0x28
                + ((unsigned int)*(unsigned short *)(param_1 + 0x6e) + *(int *)(node + 8)) * 200
                + param_1 + 0x10be) = 0x1f;
            NNS_FndRemoveListObject((void *)(param_1 + 0x19b8), node);
            if (node != 0) {
                NNSi_FndFreeFromDefaultHeap(node);
            }
            *(int *)(row + 0x184c) = 0;
            node = next;
            row = row + 0x28;
        } while (next != 0);
    }
}
