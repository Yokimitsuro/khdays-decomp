typedef struct {
    int x;
    int y;
    int z;
} func_0202b450_vec;

extern void func_020293fc(void *ptr);

void func_0202b450(int *ptr, func_0202b450_vec *src) {
    if ((ptr[0] & 0x10) == 0) {
        func_020293fc((char *)ptr + 0x110);
    }

    *(func_0202b450_vec *)((char *)ptr + 0xa8) = *src;
}
