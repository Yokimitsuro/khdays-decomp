typedef unsigned short u16;

typedef struct NNSFndList {
    void *head;
    void *tail;
    u16 count;
    u16 linkOffset;
} NNSFndList;

typedef int (*NNSFndCompare)(void *left, void *right);

extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);
extern void func_ov008_02056718(NNSFndList *destination,
                                NNSFndList *leftList,
                                NNSFndList *rightList,
                                NNSFndCompare compare);

void
func_ov008_0205684c(NNSFndList *list, NNSFndCompare compare)
{
    void *slow;
    void *fast;
    u16 leftCount;
    NNSFndList leftList;
    NNSFndList rightList;

    slow = NNS_FndGetNextListObject(list, 0);
    if (slow == 0) {
        return;
    }
    fast = NNS_FndGetNextListObject(list, slow);
    if (fast == 0) {
        return;
    }

    fast = NNS_FndGetNextListObject(list, fast);
    leftCount = 1;
    while (fast != 0) {
        slow = NNS_FndGetNextListObject(list, slow);
        fast = NNS_FndGetNextListObject(list, fast);
        if (fast != 0) {
            fast = NNS_FndGetNextListObject(list, fast);
        }
        leftCount++;
    }

    leftList = *list;
    rightList = *list;

    rightList.head = NNS_FndGetNextListObject(list, slow);
    *(void **)((char *)rightList.head + rightList.linkOffset) = 0;
    rightList.count = (u16)(list->count - leftCount);
    leftList.tail = slow;
    *(void **)((char *)slow + leftList.linkOffset + 4) = 0;
    leftList.count = leftCount;

    func_ov008_0205684c(&leftList, compare);
    func_ov008_0205684c(&rightList, compare);

    list->head = 0;
    list->tail = 0;
    list->count = 0;
    func_ov008_02056718(list, &leftList, &rightList, compare);
}
