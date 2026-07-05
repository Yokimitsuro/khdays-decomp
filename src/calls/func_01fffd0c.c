/* List_RemoveByHandle: find the node in the sorted doubly-linked list whose
 * handle field (+0xc) matches, unlink it, free it, and decrement the count.
 * func_0203d194 = FreeInstanceMemory. Pairs with List_InsertSorted (0x01fffca8). */
extern void func_0203d194(void *block);

typedef struct Block {
    struct Block *prev;   /* +0x0 */
    struct Block *next;   /* +0x4 */
    unsigned int addr;    /* +0x8 */
    void *handle;         /* +0xc */
} Block;

typedef struct BlockList {
    void *reserved0;
    Block *head;          /* +0x4 */
    void *reserved8;
    void *reservedc;
    Block terminator;     /* +0x10 */
    int count;            /* +0x20 */
} BlockList;

int func_01fffd0c(BlockList *list, void *handle)
{
    Block *node;

    for (node = list->head; node != &list->terminator; node = node->next) {
        if (node->handle == handle) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            func_0203d194(node);
            list->count--;
            return 1;
        }
    }
    return 0;
}
