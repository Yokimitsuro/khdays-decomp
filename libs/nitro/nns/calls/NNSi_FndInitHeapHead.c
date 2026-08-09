typedef unsigned int u32;
typedef unsigned short u16;
typedef signed long s32;

struct NNSFndLink {
    void *prev_object;
    void *next_object;
};

struct NNSFndList {
    void *head_object;
    void *tail_object;
    u16 num_objects;
    u16 offset;
};

struct NNSiFndHeapHead {
    u32 signature;
    struct NNSFndLink link;
    struct NNSFndList child_list;
    void *heap_start;
    void *heap_end;
    u32 attribute;
};

extern int data_02047350;
extern struct NNSFndList data_02047354;

extern void NNS_FndInitList(struct NNSFndList *list, s32 linkOffset);
extern struct NNSFndList *FindListContainHeap(const void *memoryBlock);
extern void NNS_FndAppendListObject(struct NNSFndList *list, void *object);

void NNSi_FndInitHeapHead(
    struct NNSiFndHeapHead *head,
    u32 signature,
    void *heapStart,
    void *heapEnd,
    u16 optionFlag)
{
    head->signature = signature;
    head->heap_start = heapStart;
    head->heap_end = heapEnd;
    head->attribute = 0;
    head->attribute &= ~0xff;
    head->attribute |= optionFlag & 0xff;
    NNS_FndInitList(&head->child_list, 4);
    if (!data_02047350) {
        NNS_FndInitList(&data_02047354, 4);
        data_02047350 = 1;
    }
    NNS_FndAppendListObject(FindListContainHeap(head), head);
}
