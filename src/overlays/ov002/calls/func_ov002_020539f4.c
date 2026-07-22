/* Point the current-entry slot at +0x94 at the list entry whose first word
 * matches the key, or at the fallback record embedded at +0x54 when the list has
 * none. */
extern void *NNS_FndGetNextListObject(void *list, void *from);

extern char *data_ov002_0207f60c;

void func_ov002_020539f4(int key) {
    char *ctx = data_ov002_0207f60c;
    int *node = NNS_FndGetNextListObject(ctx + 0x98, 0);

    while (node != 0) {
        if (*node == key) {
            *(int **)(ctx + 0x94) = node;
            break;
        }
        node = NNS_FndGetNextListObject(ctx + 0x98, node);
    }

    if (node == 0) {
        *(char **)(ctx + 0x94) = ctx + 0x54;
    }
}
