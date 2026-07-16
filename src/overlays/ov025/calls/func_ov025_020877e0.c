/* func_ov025_020877e0 -- count the total entries in a node's two child lists, ov008.
 * Walks the intrusive list at obj+8 and the one at obj+0x14 (NNS_FndGetNextListObject),
 * returning the combined node count. */
extern void *NNS_FndGetNextListObject(void *list, void *prev);

int func_ov025_020877e0(int obj) {
    int count = 0;
    void *node;
    for (node = NNS_FndGetNextListObject((void *)(obj + 8), 0); node != 0;
         node = NNS_FndGetNextListObject((void *)(obj + 8), node)) {
        count++;
    }
    for (node = NNS_FndGetNextListObject((void *)(obj + 0x14), 0); node != 0;
         node = NNS_FndGetNextListObject((void *)(obj + 0x14), node)) {
        count++;
    }
    return count;
}
