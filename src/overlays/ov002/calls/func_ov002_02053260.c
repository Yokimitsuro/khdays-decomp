/* Drain the NNS list at +0xb0 of the ov002 context: for every object, take its
 * successor first, unlink it, free the buffer its first word points at, then
 * free the object itself. Both frees are null-checked even though the loop
 * condition already proves the object non-null. */
extern int data_ov002_0207f60c;

extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void NNS_FndRemoveListObject(void *list, void *obj);
extern void NNSi_FndFreeFromDefaultHeap(void *p);

void func_ov002_02053260(void) {
    void **node;
    char *ctx = (char *)*(int *)&data_ov002_0207f60c;

    node = (void **)NNS_FndGetNextListObject(ctx + 0xb0, 0);
    while (node != 0) {
        void **next = (void **)NNS_FndGetNextListObject(ctx + 0xb0, node);

        NNS_FndRemoveListObject(ctx + 0xb0, node);
        if (node[0] != 0) {
            NNSi_FndFreeFromDefaultHeap(node[0]);
        }
        if (node != 0) {
            NNSi_FndFreeFromDefaultHeap(node);
        }
        node = next;
    }
}
