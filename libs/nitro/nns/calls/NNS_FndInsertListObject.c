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

extern void NNS_FndAppendListObject(struct NNSFndList *list, void *object);
extern void NNS_FndPrependListObject(struct NNSFndList *list, void *object);

void NNS_FndInsertListObject(struct NNSFndList *list, void *where, void *object)
{
    if (where == 0) {
        NNS_FndAppendListObject(list, object);
    } else if (where == list->head_object) {
        NNS_FndPrependListObject(list, object);
    } else {
        struct NNSFndLink *link =
            (struct NNSFndLink *)((char *)object + list->offset);
        void *previousObject =
            ((struct NNSFndLink *)((char *)where + list->offset))->prev_object;
        struct NNSFndLink *previousLink =
            (struct NNSFndLink *)((char *)previousObject + list->offset);
        link->prev_object = previousObject;
        link->next_object = where;
        previousLink->next_object = object;
        ((struct NNSFndLink *)((char *)where + list->offset))->prev_object = object;
        list->num_objects++;
    }
}
