typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000


/* NitroSDK os_alloc.c: the arena heap allocator (free-list cells of 32-byte-aligned blocks). */
typedef int OSArenaId;
typedef int OSHeapHandle;
#define OS_ARENA_MAX 9

#define OFFSET(n, a)    (((u32) (n)) & ((a) - 1))
#define TRUNC(n, a)     (((u32) (n)) & ~((a) - 1))
#define ROUND(n, a)     (((u32) (n) + (a) - 1) & ~((a) - 1))

#define ALIGNMENT       32
#define MINOBJSIZE      (HEADERSIZE + ALIGNMENT)
#define HEADERSIZE      ROUND(sizeof(Cell), ALIGNMENT)

typedef struct Cell Cell;
typedef struct HeapDesc HeapDesc;

struct Cell {
    Cell *prev;                   /* 0x00 */
    Cell *next;                   /* 0x04 */
    long size;                    /* 0x08 */
};

struct HeapDesc {
    long size;                    /* 0x00 */
    Cell *free;                   /* 0x04 */
    Cell *allocated;              /* 0x08 */
};

typedef struct {
    volatile OSHeapHandle currentHeap;   /* 0x00 */
    int numHeaps;                 /* 0x04 */
    void *arenaStart;             /* 0x08 */
    void *arenaEnd;               /* 0x0c */
    HeapDesc *heapArray;          /* 0x10 */
} OSHeapInfo;

extern void *data_02044590[OS_ARENA_MAX];   /* OSiHeapInfo */
#define OSiHeapInfo data_02044590
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern Cell *DLAddFront(Cell *list, Cell *cell);
extern Cell *DLExtract(Cell *list, Cell *cell);

/* OS_AllocFromHeap -- NitroSDK os_alloc.c. */
void * OS_AllocFromHeap (OSArenaId id, OSHeapHandle heap, u32 size)
{
    OSHeapInfo * heapInfo;
    HeapDesc * hd;
    Cell * cell;
    Cell * newCell;
    long leftoverSize;
    OSIntrMode enabled = OS_DisableInterrupts();


    heapInfo = OSiHeapInfo[id];

    if (!heapInfo) {
        (void)OS_RestoreInterrupts(enabled);
        return NULL;
    }

    if (heap < 0) {
        heap = heapInfo->currentHeap;
    }


    hd = &heapInfo->heapArray[heap];

    size += HEADERSIZE;
    size = ROUND(size, ALIGNMENT);

    for (cell = hd->free; cell != NULL; cell = cell->next) {
        if ((long)size <= cell->size) {
            break;
        }
    }

    if (cell == NULL) {
        (void)OS_RestoreInterrupts(enabled);
        return NULL;
    }


    leftoverSize = cell->size - (long)size;

    if (leftoverSize < MINOBJSIZE) {
        hd->free = DLExtract(hd->free, cell);
    } else {
        cell->size = (long)size;
        newCell = (Cell *) ((char *)cell + size);
        newCell->size = leftoverSize;
        newCell->prev = cell->prev;
        newCell->next = cell->next;

        if (newCell->next != NULL) {
            newCell->next->prev = newCell;
        }

        if (newCell->prev != NULL) {
            newCell->prev->next = newCell;
        } else {
            hd->free = newCell;
        }
    }

    hd->allocated = DLAddFront(hd->allocated, cell);


    (void)OS_RestoreInterrupts(enabled);
    return (void *)((char *)cell + HEADERSIZE);
}
