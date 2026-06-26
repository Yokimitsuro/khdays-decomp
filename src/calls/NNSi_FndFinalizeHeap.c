extern int NNS_FndRemoveListObject();
extern int FindListContainHeap();

int NNSi_FndFinalizeHeap(int a) {
    return NNS_FndRemoveListObject(FindListContainHeap(a), a);
}
