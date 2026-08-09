typedef unsigned int u32;
typedef unsigned short u16;

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

struct NNSiFndExpHeapMBlockHead {
    u16 signature;
    u16 attribute;
    u32 block_size;
    struct NNSiFndExpHeapMBlockHead *prev_block;
    struct NNSiFndExpHeapMBlockHead *next_block;
};

struct NNSiFndExpMBlockList {
    struct NNSiFndExpHeapMBlockHead *head;
    struct NNSiFndExpHeapMBlockHead *tail;
};

struct NNSiFndExpHeapHead {
    struct NNSiFndExpMBlockList free_list;
    struct NNSiFndExpMBlockList used_list;
    u16 group_id;
    u16 feature;
};

struct NNSiMemRegion {
    void *start;
    void *end;
};

extern void NNSi_FndInitHeapHead(
    struct NNSiFndHeapHead *head,
    u32 signature,
    void *heapStart,
    void *heapEnd,
    u16 optionFlag);
extern struct NNSiFndExpHeapMBlockHead *InitMBlock(const struct NNSiMemRegion *region, u16 signature);

struct NNSiFndHeapHead *InitExpHeap(void *startAddress, void *endAddress, u16 optionFlag)
{
    struct NNSiFndHeapHead *heapHead = (struct NNSiFndHeapHead *)startAddress;
    struct NNSiFndExpHeapHead *expHeapHead =
        (struct NNSiFndExpHeapHead *)((char *)heapHead + sizeof(struct NNSiFndHeapHead));
    struct NNSiFndExpHeapMBlockHead *block;
    struct NNSiMemRegion region;

    NNSi_FndInitHeapHead(
        heapHead,
        0x45585048,
        (char *)expHeapHead + sizeof(struct NNSiFndExpHeapHead),
        endAddress,
        optionFlag);
    expHeapHead->group_id = 0;
    expHeapHead->feature = 0;
    expHeapHead->feature &= ~1;
    expHeapHead->feature |= 0 & 1;

    region.start = heapHead->heap_start;
    region.end = heapHead->heap_end;
    block = InitMBlock(&region, 0x4652);

    expHeapHead->free_list.head = block;
    expHeapHead->free_list.tail = block;
    expHeapHead->used_list.head = 0;
    expHeapHead->used_list.tail = 0;

    return heapHead;
}
