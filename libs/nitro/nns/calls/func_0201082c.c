typedef unsigned int u32;
typedef unsigned short u16;

struct NnsFndLink {
    void *previousObject;
    void *nextObject;
};

struct NnsFndList {
    void *headObject;
    void *tailObject;
    u16 objectCount;
    u16 linkOffset;
};

struct NnsFndHeapHead {
    u32 signature;
    struct NnsFndLink link;
    struct NnsFndList childList;
    void *heapStart;
    void *heapEnd;
    u32 attribute;
};

struct NnsFndExpHeapBlock {
    u16 signature;
    u16 attribute;
    u32 blockSize;
    struct NnsFndExpHeapBlock *previousBlock;
    struct NnsFndExpHeapBlock *nextBlock;
};

struct NnsFndExpBlockList {
    struct NnsFndExpHeapBlock *head;
    struct NnsFndExpHeapBlock *tail;
};

struct NnsFndExpHeapHead {
    struct NnsFndExpBlockList freeList;
    struct NnsFndExpBlockList usedList;
    u16 groupId;
    u16 feature;
};

struct NnsMemoryRegion {
    void *start;
    void *end;
};

extern void GetRegionOfMBlock(
    struct NnsMemoryRegion *region,
    struct NnsFndExpHeapBlock *block);
extern struct NnsFndExpHeapBlock *RemoveMBlock(
    struct NnsFndExpBlockList *list,
    struct NnsFndExpHeapBlock *block);
extern struct NnsFndExpHeapBlock *InitMBlock(
    const struct NnsMemoryRegion *region,
    u16 signature);
extern struct NnsFndExpHeapBlock *InsertMBlock(
    struct NnsFndExpBlockList *list,
    struct NnsFndExpHeapBlock *target,
    struct NnsFndExpHeapBlock *previous);
extern void INITi_CpuClear32_0x01ff86fc(u32 value, void *destination, u32 size);
extern int RecycleRegion(
    struct NnsFndExpHeapHead *expHeapHead,
    const struct NnsMemoryRegion *region);

static inline void *AddToPointer(void *pointer, u32 value)
{
    return (void *)(value + (u32)pointer);
}

static inline void *GetMemoryForBlock(struct NnsFndExpHeapBlock *block)
{
    return (char *)block + sizeof(struct NnsFndExpHeapBlock);
}

static inline void *GetBlockEnd(struct NnsFndExpHeapBlock *block)
{
    return AddToPointer(GetMemoryForBlock(block), block->blockSize);
}

static inline u32 GetOffsetFromPointers(const void *start, const void *end)
{
    return (u32)end - (u32)start;
}

static inline void FillAllocMemory(
    struct NnsFndHeapHead *heapHead,
    void *address,
    u32 size)
{
    if (((u16)(heapHead->attribute & 0xff)) & 1) {
        INITi_CpuClear32_0x01ff86fc(0, address, size);
    }
}

u32 func_0201082c(
    struct NnsFndHeapHead *heapHead,
    void *memoryBlock,
    u32 size)
{
    struct NnsFndExpHeapHead *expHeapHead =
        (struct NnsFndExpHeapHead *)((char *)heapHead + sizeof(struct NnsFndHeapHead));
    struct NnsFndExpHeapBlock *block;
    u32 oldBlockSize =
        ((struct NnsFndExpHeapBlock *)
            ((char *)memoryBlock - sizeof(struct NnsFndExpHeapBlock)))->blockSize;
    struct NnsFndExpHeapBlock *blockHead =
        (struct NnsFndExpHeapBlock *)((char *)memoryBlock - sizeof(struct NnsFndExpHeapBlock));

    size = (size + 3) & ~3;
    if (size == oldBlockSize) {
        return size;
    }

    if (size > oldBlockSize) {
        void *currentUsedEnd = GetBlockEnd(blockHead);

        for (block = expHeapHead->freeList.head; block; block = block->nextBlock) {
            if (block == currentUsedEnd) {
                break;
            }
        }
        if (!block ||
            size > oldBlockSize + sizeof(struct NnsFndExpHeapBlock) + block->blockSize) {
            return 0;
        }

        struct NnsMemoryRegion newFreeRegion;
        void *oldFreeStart;
        struct NnsFndExpHeapBlock *nextBlockPrevious;

        GetRegionOfMBlock(&newFreeRegion, block);
        nextBlockPrevious = RemoveMBlock(&expHeapHead->freeList, block);
        oldFreeStart = newFreeRegion.start;
        newFreeRegion.start = AddToPointer(memoryBlock, size);
        if (GetOffsetFromPointers(newFreeRegion.start, newFreeRegion.end) <
            sizeof(struct NnsFndExpHeapBlock)) {
            newFreeRegion.start = newFreeRegion.end;
        }
        blockHead->blockSize = GetOffsetFromPointers(memoryBlock, newFreeRegion.start);
        if (GetOffsetFromPointers(newFreeRegion.start, newFreeRegion.end) >=
            sizeof(struct NnsFndExpHeapBlock)) {
            InsertMBlock(
                &expHeapHead->freeList,
                InitMBlock(&newFreeRegion, 0x4652),
                nextBlockPrevious);
        }
        FillAllocMemory(
            heapHead,
            oldFreeStart,
            GetOffsetFromPointers(oldFreeStart, newFreeRegion.start));
    } else {
        struct NnsMemoryRegion newFreeRegion;
        newFreeRegion.start = AddToPointer(memoryBlock, size);
        newFreeRegion.end = GetBlockEnd(blockHead);
        blockHead->blockSize = size;
        if (!RecycleRegion(expHeapHead, &newFreeRegion)) {
            blockHead->blockSize = oldBlockSize;
        }
    }

    return blockHead->blockSize;
}
