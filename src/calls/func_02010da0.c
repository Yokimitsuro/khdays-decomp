extern int OS_AllocFromHeap();

int func_02010da0(int arg0, int arg1) {
    return OS_AllocFromHeap(*(int *)(arg0 + 8), *(int *)(arg0 + 4), arg1, arg0);
}
