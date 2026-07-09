extern int OS_FreeToHeap();

int func_02010dbc(int arg0, int arg1) {
    return OS_FreeToHeap(*(int *)(arg0 + 8), *(int *)(arg0 + 4), arg1, arg0);
}
