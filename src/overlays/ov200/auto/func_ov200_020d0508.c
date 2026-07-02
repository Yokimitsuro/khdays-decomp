typedef struct {
    char pad[0x38];
    int type : 4;
    int state : 4;
} Node;

void func_ov200_020d0508(Node *node, int active) {
    if (active != 0) {
        node->state = 1;
    } else if (node->type == 1) {
        node->state = 2;
    }
}
