typedef unsigned short u16;

typedef struct NNSFndList {
    void *head;
    void *tail;
    u16 count;
    u16 linkOffset;
} NNSFndList;

typedef int (*NNSFndCompare)(void *left, void *right);

extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);
extern void NNS_FndRemoveListObject(NNSFndList *list, void *object);
extern void NNS_FndAppendListObject(NNSFndList *list, void *object);

void
func_ov008_02056718(NNSFndList *destination, NNSFndList *leftList,
                    NNSFndList *rightList, NNSFndCompare compare)
{
    void *left;
    void *right;

    while (1) {
        left = NNS_FndGetNextListObject(leftList, 0);
        right = NNS_FndGetNextListObject(rightList, 0);
        if (left == 0) {
            right = NNS_FndGetNextListObject(rightList, 0);
            if (right != 0) {
                *(void **)((char *)destination->tail +
                           destination->linkOffset + 4) = right;
                *(void **)((char *)right + rightList->linkOffset) =
                    destination->tail;
                destination->tail = rightList->tail;
                destination->count =
                    (u16)(destination->count + rightList->count);
            }
            break;
        } else if (right == 0) {
            left = NNS_FndGetNextListObject(leftList, 0);
            if (left != 0) {
                *(void **)((char *)destination->tail +
                           destination->linkOffset + 4) = left;
                *(void **)((char *)left + leftList->linkOffset) =
                    destination->tail;
                destination->tail = leftList->tail;
                destination->count =
                    (u16)(destination->count + leftList->count);
            }
            break;
        } else if (compare(left, right) != 0) {
            NNS_FndRemoveListObject(rightList, right);
            NNS_FndAppendListObject(destination, right);
        } else {
            NNS_FndRemoveListObject(leftList, left);
            NNS_FndAppendListObject(destination, left);
        }
    }
}
