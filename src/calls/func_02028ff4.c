/* func_02028ff4 -- insert an item into a quadtree, MAIN. The item's box (+0xc..+0x18) is tested
 * against the centre of the node's square `rect` (centre x/y, side): when it lies wholly inside one
 * quadrant (0 top-left, 1 top-right, 2 bottom-left, 3 bottom-right) and that child exists, the
 * quadrant's bit (0x1000 << q) is raised on the node and the item descends with the child's square
 * (centre moved by a quarter side, half the side). Otherwise the item is pushed on the node's list. */
typedef unsigned short u16;

typedef struct QuadItem {
    struct QuadNode *owner;             /* +0x00 */
    struct QuadItem *next;              /* +0x04 */
    struct QuadItem *prev;              /* +0x08 */
    int minX;                           /* +0x0c */
    int minY;                           /* +0x10 */
    int maxX;                           /* +0x14 */
    int maxY;                           /* +0x18 */
} QuadItem;

typedef struct QuadNode {
    u16 flags;                          /* +0x00 */
    u16 pad02;
    int pad04;
    QuadItem *head;                     /* +0x08 */
    int pad0c;
    struct QuadNode *child[4];          /* +0x10 */
} QuadNode;

typedef struct QuadRect {
    int x;
    int y;
    int size;
} QuadRect;

void func_02028ff4(QuadNode *node, const QuadRect *rect, QuadItem *item)
{
    int quarter = rect->size / 4;
    int q = -1;
    QuadRect sub;

    if (item->maxX < rect->x) {
        if (item->maxY < rect->y) {
            q = 0;
        } else if (item->minY >= rect->y) {
            q = 2;
        }
    } else if (item->minX >= rect->x) {
        if (item->maxY < rect->y) {
            q = 1;
        } else if (item->minY >= rect->y) {
            q = 3;
        }
    }
    if (q < 0 || node->child[q] == 0) {
        item->next = node->head;
        if (item->next != 0) {
            node->head->prev = item;
        }
        node->head = item;
        item->owner = node;
        return;
    }
    switch (q) {
    case 0:
        sub.x = rect->x - quarter;
        sub.y = rect->y - quarter;
        break;
    case 1:
        sub.x = rect->x + quarter;
        sub.y = rect->y - quarter;
        break;
    case 2:
        sub.x = rect->x - quarter;
        sub.y = rect->y + quarter;
        break;
    default:
        sub.x = rect->x + quarter;
        sub.y = rect->y + quarter;
        break;
    }
    sub.size = rect->size / 2;
    node->flags |= 0x1000 << q;
    func_02028ff4(node->child[q], &sub, item);
}
