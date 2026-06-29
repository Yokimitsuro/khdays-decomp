extern unsigned char *func_01fffd70(void *ptr);
extern unsigned char *func_01fffd8c(void *ptr);

int func_0203c650(void *ptr, int value) {
    unsigned char *node;

    if (value == 0) {
        return 0;
    }

    node = func_01fffd70(ptr);
    while (node != 0) {
        if (*(int *)(node + 0x1c) == value) {
            *(int *)(node + 0x24) = 1;
            return 1;
        }

        node = func_01fffd8c(ptr);
    }

    return 0;
}
