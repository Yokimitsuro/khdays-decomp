typedef struct func_02010314_node {
    char pad[8];
    struct func_02010314_node *prev;
    struct func_02010314_node *next;
} func_02010314_node;

typedef struct {
    func_02010314_node *head;
    func_02010314_node *tail;
} func_02010314_list;

func_02010314_node *func_02010314(func_02010314_list *list, func_02010314_node *node, func_02010314_node *prev)
{
    func_02010314_node *next;

    node->prev = prev;
    if (prev != 0) {
        next = prev->next;
        prev->next = node;
    } else {
        next = list->head;
        list->head = node;
    }
    node->next = next;
    if (next != 0) {
        next->prev = node;
    } else {
        list->tail = node;
    }
    return node;
}
