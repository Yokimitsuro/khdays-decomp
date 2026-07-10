extern unsigned int *func_0203d15c(int size);

unsigned int func_01fffca8(int list, int extra, unsigned int key) {
    unsigned int *slot;
    unsigned int prev;
    unsigned int *node = *(unsigned int **)(list + 4);
    while (node[2] <= key)
        node = (unsigned int *)node[1];
    prev = node[0];
    slot = func_0203d15c(extra + 0x10);
    slot[0] = prev;
    slot[1] = (unsigned int)node;
    *(unsigned int **)(prev + 4) = slot;
    node[0] = (unsigned int)slot;
    slot[2] = key;
    slot[3] = (unsigned int)(slot + 4);
    *(int *)(list + 0x20) = *(int *)(list + 0x20) + 1;
    return slot[3];
}
