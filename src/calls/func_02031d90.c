typedef unsigned int u32;

struct Node {
    char _00[0x5c];
    struct Node *next;
};

extern struct Node *func_02023660(int size);
extern void func_02011f3c(void *);
extern void func_02011f68(void *);
extern void MI_CpuFill8(void *dst, int val, u32 n);
extern void func_02031c58(void *a, void *b, struct Node *node);

int func_02031d90(void *a, void *b)
{
    struct Node *node;
    struct Node *cur;
    int count;

    count = 0;
    node = func_02023660(0x64);
    func_02011f3c((char *)node + 0x34);
    func_02011f68((char *)node + 0x20);
    MI_CpuFill8(node, 0, 0x20);
    func_02031c58(a, b, node);
    cur = *(struct Node **)((char *)a + 0x4620);
    if (cur == 0) {
        *(struct Node **)((char *)a + 0x4620) = node;
    } else {
        struct Node *nx;
        nx = cur->next;
        count++;
        while (nx != 0) {
            cur = nx;
            nx = cur->next;
            count++;
        }
        cur->next = node;
    }
    node->next = 0;
    return count;
}
