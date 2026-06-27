extern void DC_StoreRange(void *addr, unsigned size);
extern void SNDi_UnlockMutex_0x020084f4(void);
extern void SNDi_UnlockMutex_0x02008508(void);

struct Node {
    char pad0[4];
    struct Node *next; /* +0x04 */
    char pad1[0x10];
    struct Node *link; /* +0x18 */
};

struct Slot {
    struct Node *head;
    void *repl;
};

struct Mgr {
    char pad0[0x18];
    struct Slot list[4]; /* +0x18 .. +0x38 */
};

void func_02008f44(struct Mgr *mgr) {
    struct Node *sentinel;
    int i;
    struct Node *node;
    struct Node *p;
    struct Node *q;

    SNDi_UnlockMutex_0x020084f4();
    sentinel = (struct Node *)&mgr->list[0];
    for (i = 0; i < 4; i++) {
        node = mgr->list[i].head;
        if (node != 0) {
            p = node->link;
            if (sentinel == p) {
                node->link = (struct Node *)mgr->list[i].repl;
                DC_StoreRange(node, 0x3c);
            } else {
                if (p != 0) {
                    do {
                        q = p->next;
                        if (sentinel == q) break;
                        p = q;
                    } while (q != 0);
                }
                p->next = (struct Node *)mgr->list[i].repl;
                DC_StoreRange(p, 8);
            }
        }
        sentinel = (struct Node *)((char *)sentinel + 8);
    }
    SNDi_UnlockMutex_0x02008508();
}
