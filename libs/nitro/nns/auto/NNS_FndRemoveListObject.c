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

void NNS_FndRemoveListObject(struct NNSFndList *list, void *object)
{
    struct NNSFndLink *link =
        (struct NNSFndLink *)((char *)object + list->offset);
    if (link->prev_object == 0) {
        list->head_object = link->next_object;
    } else {
        ((struct NNSFndLink *)((char *)link->prev_object + list->offset))->next_object =
            link->next_object;
    }
    if (link->next_object == 0) {
        list->tail_object = link->prev_object;
    } else {
        ((struct NNSFndLink *)((char *)link->next_object + list->offset))->prev_object =
            link->prev_object;
    }
    link->prev_object = 0;
    link->next_object = 0;
    list->num_objects--;
}
