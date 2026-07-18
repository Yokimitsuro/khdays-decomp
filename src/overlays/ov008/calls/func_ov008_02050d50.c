/*
 * func_ov008_02050d50 -- x3 (ov008/...). Remove one object from the shared UI list and free it.
 * The list header lives at *(data_02090f04+4) + 0x9660. Walk it with NNS_FndGetNextListObject; when
 * the entry equal to `obj` is found, unlink it with NNS_FndRemoveListObject and, if non-null, release
 * it via NNSi_FndFreeFromDefaultHeap. Stops if the list runs out.
 *
 * The match/free handling sits inside the loop (before the advance) so mwcc lays the "found" block as
 * the fall-through after the compare and the list-advance as the out-of-line back-edge -- matching the
 * ROM's `cmp; bne <advance>` block order.
 */
extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern void NNS_FndRemoveListObject(void *list, void *obj);
extern void NNSi_FndFreeFromDefaultHeap(void *obj);
extern int data_ov008_02090f04[];

void func_ov008_02050d50(void *obj) {
    void *node = NNS_FndGetNextListObject((void *)(data_ov008_02090f04[1] + 0x9660), 0);

    if (node == 0) {
        return;
    }
    for (;;) {
        if (node == obj) {
            NNS_FndRemoveListObject((void *)(data_ov008_02090f04[1] + 0x9660), obj);
            if (obj != 0) {
                NNSi_FndFreeFromDefaultHeap(obj);
            }
            return;
        }
        node = NNS_FndGetNextListObject((void *)(data_ov008_02090f04[1] + 0x9660), node);
        if (node == 0) {
            return;
        }
    }
}
