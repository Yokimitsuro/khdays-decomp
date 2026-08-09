typedef signed int s32;
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

extern void *func_020103e4(
    struct NNSiFndExpHeapHead *expHeapHead,
    struct NNSiFndExpHeapMBlockHead *freeBlock,
    void *memoryBlock,
    u32 size,
    u16 direction);

static inline u16 GetAllocationMode(struct NNSiFndExpHeapHead *expHeapHead)
{
    return (u16)((expHeapHead->feature >> 0) & 1);
}

static inline void *GetMemoryForBlock(struct NNSiFndExpHeapMBlockHead *block)
{
    return (char *)block + sizeof(struct NNSiFndExpHeapMBlockHead);
}

static inline void *AddToPointer(void *pointer, u32 value)
{
    return (void *)(value + (u32)pointer);
}

static inline void *SubtractFromPointer(void *pointer, u32 value)
{
    return (void *)((u32)pointer - value);
}

static inline void *RoundDownPointer(void *pointer, u32 alignment)
{
    return (void *)(~(alignment - 1) & (u32)pointer);
}

static inline s32 ComparePointers(const void *left, const void *right)
{
    const unsigned char *leftBytes = left;
    const unsigned char *rightBytes = right;
    return leftBytes - rightBytes;
}

void *AllocFromTail(struct NNSiFndHeapHead *heapHead, u32 size, s32 alignment)
{
    struct NNSiFndExpHeapHead *expHeapHead =
        (struct NNSiFndExpHeapHead *)((char *)heapHead + sizeof(struct NNSiFndHeapHead));
    const s32 allocateFirst = GetAllocationMode(expHeapHead) == 0;
    struct NNSiFndExpHeapMBlockHead *block = 0;
    struct NNSiFndExpHeapMBlockHead *foundBlock = 0;
    u32 foundSize = 0xffffffff;
    void *foundMemory = 0;

    for (block = expHeapHead->free_list.tail; block; block = block->prev_block) {
        void *const memory = GetMemoryForBlock(block);
        void *const memoryEnd = AddToPointer(memory, block->block_size);
        void *const requestedMemory =
            RoundDownPointer(SubtractFromPointer(memoryEnd, size), alignment);
        if (ComparePointers(requestedMemory, memory) >= 0 && foundSize > block->block_size) {
            foundBlock = block;
            foundSize = block->block_size;
            foundMemory = requestedMemory;
            if (allocateFirst || foundSize == size) {
                break;
            }
        }
    }

    if (!foundBlock) {
        return 0;
    }

    return func_020103e4(expHeapHead, foundBlock, foundMemory, size, 1);
}
