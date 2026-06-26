typedef int (*fn)();

int NNS_FndFreeToAllocator(fn **p, int a) {
    return (*p)[1]((int)p, a);
}
