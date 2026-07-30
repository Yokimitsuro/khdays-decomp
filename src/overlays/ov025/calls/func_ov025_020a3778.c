/* func_ov025_020a3778 -- Ov008_InsertListEntry (208 B, 8 relocs).
 * Allocates a fresh 0x30-byte menu list node from the default heap, zeroes it, fills its fields
 * from the params (id, kind, and four payload words), duplicates the UTF-16 label into its own
 * heap buffer (node->label, size (wcslen+1)*2), and inserts the node into the list at self+0x1cc
 * in sorted order: it scans for the first node in the same kind-group whose id is greater than the
 * new id and inserts before it. Called by func_ov008_0206e410 when the (kind,id) entry is new. */
typedef struct {
    int   id;      /* 0x00 */
    int   link;    /* 0x04 */
    int   kind;    /* 0x08 */
    int   f0c;     /* 0x0c */
    int   f10;     /* 0x10 */
    void *label;   /* 0x14 */
    int   f18;     /* 0x18 */
    int   f1c;     /* 0x1c */
    int   f20;     /* 0x20 */
    int   pad[3];  /* 0x24 */
} Ov008ListNode;

extern char *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void  MI_CpuFill8(void *dst, int data, int size);
extern int   func_020200c8(short *s);
extern void  MIi_CpuCopy16(const void *src, void *dest, unsigned int size);
extern int   NNS_FndGetNextListObject(void *list, int obj);
extern void  NNS_FndInsertListObject(void *list, int before, int item);

void func_ov025_020a3778(int self, int id, int kind, int p4, int p5, int p6, int p7, int p8, short *label)
{
    Ov008ListNode *node = (Ov008ListNode *)NNSi_FndAllocFromDefaultExpHeap(0x30);
    int bytes;
    int *it;

    MI_CpuFill8(node, 0, 0x30);
    bytes = (func_020200c8(label) + 1) * 2;
    node->id = id;
    node->kind = kind;
    node->f0c = p4;
    node->f10 = p5;
    node->f18 = p6;
    node->f1c = p7;
    node->f20 = p8;
    node->label = NNSi_FndAllocFromDefaultExpHeap(bytes);
    MIi_CpuCopy16(label, node->label, bytes);
    for (it = (int *)NNS_FndGetNextListObject((void *)(self + 0x1cc), 0); it != 0;
         it = (int *)NNS_FndGetNextListObject((void *)(self + 0x1cc), (int)it)) {
        if (it[2] == kind && it[0] > id)
            break;
    }
    NNS_FndInsertListObject((void *)(self + 0x1cc), (int)it, (int)node);
}
