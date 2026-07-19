/* Walks the variable-stride chain (terminated by a -1 stride) for the entry with the given id. */
void *func_ov002_0206480c(char *node, unsigned short id) {
    char *found = 0;
    int step = *(int *)node;
    if (step != -1) {
        do {
            if (*(unsigned short *)(node + 6) == id) {
                found = node;
                break;
            }
            node += step;
            step = *(int *)node;
        } while (step != -1);
    }
    return found;
}
