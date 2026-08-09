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

extern void GetRegionOfMBlock(
    struct NNSiMemRegion *region,
    struct NNSiFndExpHeapMBlockHead *block);
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
extern void INITi_CpuClear32_0x01ff86fc(u32 value, void *destination, u32 size);

static inline u32 GetOffsetFromPointers(const void *start, const void *end)
{
    return (u32)end - (u32)start;
}

static inline void FillAllocMemory(
    struct NNSiFndHeapHead *heapHead,
    void *address,
    u32 size)
{
    if (((u16)(heapHead->attribute & 0xff)) & 1) {
        INITi_CpuClear32_0x01ff86fc(0, address, size);
    }
}

static inline void SetAllocDirection(
    struct NNSiFndExpHeapMBlockHead *block,
    u16 direction)
{
    u32 maskBits = (1 << 1) - 1;
    u32 newValue = direction & maskBits;
    maskBits <<= 15;
    block->attribute &= ~maskBits;
    block->attribute |= newValue << 15;
}

static inline void SetBlockAlignment(
    struct NNSiFndExpHeapMBlockHead *block,
    u16 alignment)
{
    u32 maskBits = (1 << 7) - 1;
    u32 newValue = alignment & maskBits;
    maskBits <<= 8;
    block->attribute &= ~maskBits;
    block->attribute |= newValue << 8;
}

static inline void SetBlockGroupId(
    struct NNSiFndExpHeapMBlockHead *block,
    u16 groupId)
{
    u32 maskBits = (1 << 8) - 1;
    u32 newValue = groupId & maskBits;
    maskBits <<= 0;
    block->attribute &= ~maskBits;
    block->attribute |= newValue << 0;
}

void *func_020103e4(
    struct NNSiFndExpHeapHead *expHeapHead,
    struct NNSiFndExpHeapMBlockHead *freeBlock,
    void *memoryBlock,
    u32 size,
    u16 direction)
{
    struct NNSiMemRegion topFreeRegion;
    struct NNSiMemRegion bottomFreeRegion;
    struct NNSiFndExpHeapMBlockHead *previousFreeBlock;

    GetRegionOfMBlock(&topFreeRegion, freeBlock);

    bottomFreeRegion.end = topFreeRegion.end;
    bottomFreeRegion.start = (void *)(size + (u32)memoryBlock);
    topFreeRegion.end = (char *)memoryBlock - sizeof(struct NNSiFndExpHeapMBlockHead);

    previousFreeBlock = RemoveMBlock(&expHeapHead->free_list, freeBlock);

    if ((u32)((char *)topFreeRegion.end - (char *)topFreeRegion.start) <
        sizeof(struct NNSiFndExpHeapMBlockHead) + 4) {
        topFreeRegion.end = topFreeRegion.start;
    } else {
        previousFreeBlock = InsertMBlock(
            &expHeapHead->free_list,
            InitMBlock(&topFreeRegion, 0x4652),
            previousFreeBlock);
    }

    if ((u32)((char *)bottomFreeRegion.end - (char *)bottomFreeRegion.start) <
        sizeof(struct NNSiFndExpHeapMBlockHead) + 4) {
        bottomFreeRegion.start = bottomFreeRegion.end;
    } else {
        InsertMBlock(
            &expHeapHead->free_list,
            InitMBlock(&bottomFreeRegion, 0x4652),
            previousFreeBlock);
    }

    FillAllocMemory(
        (struct NNSiFndHeapHead *)((char *)expHeapHead - sizeof(struct NNSiFndHeapHead)),
        topFreeRegion.end,
        (u32)((char *)bottomFreeRegion.start - (char *)topFreeRegion.end));

    struct NNSiFndExpHeapMBlockHead *newUsedBlock;
    struct NNSiMemRegion usedRegion;

    usedRegion.start = (char *)memoryBlock - sizeof(struct NNSiFndExpHeapMBlockHead);
    usedRegion.end = bottomFreeRegion.start;

    newUsedBlock = InitMBlock(&usedRegion, 0x5544);

    SetAllocDirection(newUsedBlock, direction);
    SetBlockAlignment(
        newUsedBlock,
        (u16)GetOffsetFromPointers(topFreeRegion.end, newUsedBlock));
    SetBlockGroupId(newUsedBlock, expHeapHead->group_id);

    InsertMBlock(&expHeapHead->used_list, newUsedBlock, expHeapHead->used_list.tail);

    return memoryBlock;
}
