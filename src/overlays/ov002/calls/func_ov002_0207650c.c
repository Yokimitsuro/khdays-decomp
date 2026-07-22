/* Tear down every node on list `index`: walk the chain freeing each one, then
 * clear the list's own slot. The next pointer is read BEFORE the node is freed,
 * which is why it needs a local rather than a second field read.
 *
 * The tail runs whether or not the list had anything on it -- an empty list
 * still needs its slot cleared -- so the entry test branches into the tail, not
 * past it. */
extern void func_ov002_02076af0(void *node);
extern void func_ov002_02077ef8(int index);

typedef struct Ov002ListNode {
    char pad0000[4];
    struct Ov002ListNode *pNext;    /* +4 */
} Ov002ListNode;

typedef struct {
    char pad0000[4];
    Ov002ListNode **lists;          /* +4, one chain head per index */
} Ov002ListRoot;

extern Ov002ListRoot data_ov002_0207fa20;

void func_ov002_0207650c(int index) {
    Ov002ListNode *node = data_ov002_0207fa20.lists[index];

    while (node != 0) {
        Ov002ListNode *next = node->pNext;
        func_ov002_02076af0(node);
        node = next;
    }

    func_ov002_02077ef8(index);
}
