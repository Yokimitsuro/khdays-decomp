extern void *func_01fffd70(void *listHead);
extern void *func_01fffd8c(void *listHead);
extern int func_ov107_020c38ac(void *criteria, void *query, int flags);

int func_ov107_020c8f44(char *owner, void *query, void **results) {
    char *sub = *(char **)(owner + 4);
    int count = 0;
    char *listHead = sub + 0xa8;
    void *iter;
    void **node;

    iter = func_01fffd70(listHead);
    node = (iter == 0) ? 0 : *(void ***)iter;

    while (node != 0) {
        if (node[1] == *(void **)(owner + 4)) {
            void *criteria = *(void **)((char *)node + 0x1d8);
            if (func_ov107_020c38ac(criteria, query, 0) != 0) {
                results[count] = node;
                count++;
            }
        }
        iter = func_01fffd8c(listHead);
        node = (iter == 0) ? 0 : *(void ***)iter;
    }
    return count;
}
