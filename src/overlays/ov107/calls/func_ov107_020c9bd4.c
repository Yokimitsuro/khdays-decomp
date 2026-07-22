/* Rebuilds the id -> node lookup table at +0x48: allocates one pointer per registered id
 * (+0x24) and walks the intrusive list at +4, filing each node under the id in its
 * halfword at +2. */
extern void *func_0203d15c(unsigned int size);
extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);
extern char *data_ov107_020cbf1c;

void func_ov107_020c9bd4(void) {
    char *ctx = data_ov107_020cbf1c;
    char *node;
    if (ctx == 0) {
        return;
    }
    *(void **)(ctx + 0x48) = func_0203d15c(*(int *)(ctx + 0x24) * 4);
    node = func_01fffd70(ctx + 4);
    while (node != 0) {
        char *item = *(char **)node;
        *(char **)(*(char **)(ctx + 0x48) + *(unsigned short *)(item + 2) * 4) = item;
        node = func_01fffd8c(ctx + 4);
    }
}
