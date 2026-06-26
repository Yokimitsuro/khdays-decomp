int NNS_FndAllocFromAllocator(int *p, int a) {
    return (**(int (***)())p)(p, a);
}
