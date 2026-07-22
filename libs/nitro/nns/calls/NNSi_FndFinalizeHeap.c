/* Unlinks the heap from the list that contains it. */
extern void *FindListContainHeap(void *heap);
extern void NNS_FndRemoveListObject(void *list, void *heap);

void NNSi_FndFinalizeHeap(void *heap) {
    NNS_FndRemoveListObject(FindListContainHeap(heap), heap);
}
