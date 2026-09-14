/* Flattens a build-list of 4-byte entries (obtained from func_01fffd70/func_01fffd8c,
 * iterating node's list at +0xb0) into a packed array allocated at node->entries,
 * records the entry count, allocates two more count-sized buffers, then destroys and
 * frees the list and clears the pointer. */
typedef struct {
    unsigned char b0, b1, b2, b3;
} Entry4;

typedef struct {
    char pad_00[0x94];
    Entry4 *entries;    /* +0x94 */
    int entryCount;     /* +0x98 */
    void *field_9c;      /* +0x9c: count-sized buffer */
    void *field_a0;      /* +0xa0: count-sized buffer */
    char pad_a4[0xb0 - 0xa4];
    int list;            /* +0xb0 */
} Node;

extern void *func_0203d15c(unsigned int size);
extern int func_01fffd70(int list);
extern int func_01fffd8c(int list);
extern void NNSi_FndDestroyDoubleList(void *list);
extern void func_0203d194(void *object);

void func_ov107_020c9618(int nodeAddr) {
    Node *node = (Node *)nodeAddr;
    int count = *(int *)(node->list + 0x20);
    int i;
    unsigned char *p;

    node->entryCount = count;
    node->entries = (Entry4 *)func_0203d15c(count << 2);
    i = 0;
    p = (unsigned char *)func_01fffd70(node->list);
    while (p != 0) {
        node->entries[i] = *(Entry4 *)p;
        i++;
        p = (unsigned char *)func_01fffd8c(node->list);
    }
    node->field_9c = func_0203d15c(node->entryCount);
    node->field_a0 = func_0203d15c(node->entryCount);
    NNSi_FndDestroyDoubleList((void *)node->list);
    func_0203d194((void *)node->list);
    node->list = 0;
}
