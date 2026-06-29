extern int func_02020368(unsigned long long value, unsigned int arg2, int arg3);

int func_0201cbe8(int **ptr) {
    int *inner;

    if (*(int * volatile *)ptr == 0) {
        return 0;
    }

    inner = *ptr;
    return func_02020368((unsigned long long)*(unsigned int *)((char *)inner + 0x160) * 1000,
                         *(unsigned short *)((char *)inner + 0xc4),
                         0);
}
