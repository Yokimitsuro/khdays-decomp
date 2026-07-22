/* Unlink the node from its chain and, if it was a chain head, promote its
 * successor into the head table. The head table is the first 0x18 words of the
 * list table. */
typedef struct Ov002ListNode {
    struct Ov002ListNode *pPrev;    /* +0 */
    struct Ov002ListNode *pNext;    /* +4 */
} Ov002ListNode;

typedef struct {
    char pad0000[4];
    Ov002ListNode **heads;          /* +4 */
} Ov002ListRoot;

extern Ov002ListRoot data_ov002_0207fa20;

void func_ov002_020764a4(Ov002ListNode *self) {
    int i;
    Ov002ListNode **p;
    Ov002ListNode **heads;

    if (self->pNext != 0) {
        self->pNext->pPrev = self->pPrev;
    }

    if (self->pPrev != 0) {
        self->pPrev->pNext = self->pNext;
    }

    heads = data_ov002_0207fa20.heads;
    p = heads;

    for (i = 0; i < 0x18; i++) {
        if (*p == self) {
            heads[i] = self->pNext;
            return;
        }
        p++;
    }
}
