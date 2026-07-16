/* func_ov025_02090ddc -- insert a widget into a list keeping it sorted by depth, ov008.
 * Walks the list until it finds the first node whose sort key (u16 at node[0]+0x90) exceeds the
 * new item's key, and inserts the item before it (NNS_FndInsertListObject); if none is greater,
 * appends it (NNS_FndAppendListObject). */
extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern void  NNS_FndInsertListObject(void *list, int before, int item);
extern void  NNS_FndAppendListObject(void *list, int item);

void func_ov025_02090ddc(int unused, void *list, int *item) {
    int *node;
    for (node = (int *)NNS_FndGetNextListObject(list, 0); node != 0;
         node = (int *)NNS_FndGetNextListObject(list, node)) {
        if (*(unsigned short *)(*item + 0x90) < *(unsigned short *)(*node + 0x90)) {
            NNS_FndInsertListObject(list, (int)node, (int)item);
            return;
        }
    }
    NNS_FndAppendListObject(list, (int)item);
}
