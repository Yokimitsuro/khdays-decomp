extern void func_01ffa764(int arg0, unsigned char arg1);

void func_01ffbbac(int *ptr) {
    int flags = ptr[2];

    if ((flags & 0x200) == 0 && (flags & 1) != 0 && (flags & 0x100) == 0) {
        func_01ffa764(0x14, *(unsigned char *)(ptr[0] + 1));
    }

    ptr[0] += 2;
}
