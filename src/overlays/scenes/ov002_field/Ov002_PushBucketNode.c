extern char data_ov002_0207fa20[];
/* Push a field piece onto the head of room nRoom's list (a chest's trbox row +1 says its room:
 * 0102's chests are in rooms 6 and 11, 0105's in 1, 4 and 7, as their areas load them): chain the
 * old head into node[1], clear node[0], and back-link the old head to node. */
void Ov002_PushBucketNode(int nRoom, int *node) {
    int *head;
    node[1] = *(int *)(*(int *)(data_ov002_0207fa20 + 4) + nRoom * 4);
    node[0] = 0;
    head = *(int **)(*(int *)(data_ov002_0207fa20 + 4) + nRoom * 4);
    if (head != 0) {
        *head = (int)node;
    }
    *(int **)(*(int *)(data_ov002_0207fa20 + 4) + nRoom * 4) = node;
}
