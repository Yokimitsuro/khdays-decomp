struct Node02031c30 {
    char _0[0x5c];
    struct Node02031c30 *next;
};

struct Root02031c30 {
    char _0[0x4000 + 0x620];
    struct Node02031c30 *head;
};

void *func_02031c30(struct Root02031c30 *root, int count)
{
    struct Node02031c30 *p = root->head;
    int i = 0;
    if (count <= 0) return p;
    do {
        i++;
        p = p->next;
    } while (i < count);
    return p;
}
