typedef void (*func_0200d580_cb)(void *arg);

void func_0200d580(int *node) {
    while (node != 0) {
        ((func_0200d580_cb)node[0])((void *)node[1]);
        node = (int *)node[2];
    }
}
