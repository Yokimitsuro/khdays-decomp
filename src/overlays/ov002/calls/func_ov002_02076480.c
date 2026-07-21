extern char data_ov002_0207fa20[];
/* Push `node` onto the head of bucket `idx`: chain the old head into node[1], clear node[0], and
 * back-link the old head to node. */
void func_ov002_02076480(int idx, int *node) {
    int *head;
    node[1] = *(int *)(*(int *)(data_ov002_0207fa20 + 4) + idx * 4);
    node[0] = 0;
    head = *(int **)(*(int *)(data_ov002_0207fa20 + 4) + idx * 4);
    if (head != 0) {
        *head = (int)node;
    }
    *(int **)(*(int *)(data_ov002_0207fa20 + 4) + idx * 4) = node;
}
