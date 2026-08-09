typedef unsigned short u16;

struct NNSFndLink {
    void *prev_object;
    void *next_object;
};

struct NNSFndList {
    void *head_object;
    void *tail_object;
    u16 num_objects;
    u16 offset;
};

extern void SetFirstObject(struct NNSFndList *list, void *object);

void NNS_FndPrependListObject(struct NNSFndList *list, void *object)
{
    if (list->head_object == 0) {
        SetFirstObject(list, object);
    } else {
        struct NNSFndLink *link =
            (struct NNSFndLink *)((char *)object + list->offset);
        link->prev_object = 0;
        link->next_object = list->head_object;
        ((struct NNSFndLink *)((char *)list->head_object + list->offset))->prev_object = object;
        list->head_object = object;
        list->num_objects++;
    }
}
