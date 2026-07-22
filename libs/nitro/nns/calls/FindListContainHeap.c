/* Returns the child list that contains `heap`, or the root list when it is top level. */
extern void *FindContainHeap(void *list, void *heap);
extern char data_02047354;

void *FindListContainHeap(void *heap) {
    char *list = &data_02047354;
    void *found = FindContainHeap(list, heap);
    if (found != 0) {
        list = (char *)found + 0xc;
    }
    return list;
}
