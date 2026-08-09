typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;

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

extern struct NNSiFndExpHeapMBlockHead *RemoveMBlock(
    struct NNSiFndExpMBlockList *list,
    struct NNSiFndExpHeapMBlockHead *block);
extern struct NNSiFndExpHeapMBlockHead *InitMBlock(
    const struct NNSiMemRegion *region,
    u16 signature);
extern struct NNSiFndExpHeapMBlockHead *InsertMBlock(
    struct NNSiFndExpMBlockList *list,
    struct NNSiFndExpHeapMBlockHead *target,
    struct NNSiFndExpHeapMBlockHead *previous);

static inline void *GetMemoryForBlock(struct NNSiFndExpHeapMBlockHead *block)
{
    return (char *)block + sizeof(struct NNSiFndExpHeapMBlockHead);
}

static inline void *GetBlockEnd(struct NNSiFndExpHeapMBlockHead *block)
{
    return (void *)((u32)GetMemoryForBlock(block) + block->block_size);
}

static inline u32 GetOffsetFromPointers(const void *start, const void *end)
{
    return (u32)end - (u32)start;
}

s32 RecycleRegion(
    struct NNSiFndExpHeapHead *expHeapHead,
    const struct NNSiMemRegion *region)
{
    struct NNSiFndExpHeapMBlockHead *previousFreeBlock = 0;
    struct NNSiMemRegion freeRegion = *region;
    struct NNSiFndExpHeapMBlockHead *block;

    for (block = expHeapHead->free_list.head; block; block = block->next_block) {
        if (block < (struct NNSiFndExpHeapMBlockHead *)region->start) {
            previousFreeBlock = block;
            continue;
        }
        if (block == region->end) {
            freeRegion.end = GetBlockEnd(block);
            RemoveMBlock(&expHeapHead->free_list, block);
        }
        break;
    }

    if (previousFreeBlock && GetBlockEnd(previousFreeBlock) == region->start) {
        freeRegion.start = previousFreeBlock;
        previousFreeBlock = RemoveMBlock(&expHeapHead->free_list, previousFreeBlock);
    }

    if (GetOffsetFromPointers(freeRegion.start, freeRegion.end) <
        sizeof(struct NNSiFndExpHeapMBlockHead)) {
        return 0;
    }

    InsertMBlock(
        &expHeapHead->free_list,
        InitMBlock(&freeRegion, 0x4652),
        previousFreeBlock);
    return 1;
}
