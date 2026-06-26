struct Node {
    int field0;
    struct Node *next;
};

struct Obj {
    int field0;
    struct Node *head;   /* offset 4 */
    int pad8;
    int padc;
    struct Node listhead; /* offset 0x10 */
    int pad18;
    int pad1c;
    int pad20;
    struct Node *cur;    /* offset 0x24 */
};

int func_01fffd70(struct Obj *o)
{
    struct Node *n = o->head;
    o->cur = n;
    if (n == &o->listhead)
        return 0;
    return *((int *)((char *)n + 0xc));
}
