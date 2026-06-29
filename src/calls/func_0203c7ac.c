typedef void (*func_0203c7ac_cb1)(void *ptr, int arg);
typedef void (*func_0203c7ac_cb2)(void *ptr, int arg, int value);

void func_0203c7ac(int *ptr, int arg) {
    if (ptr[0x68 / 4] != 0) {
        ((func_0203c7ac_cb1)ptr[0x68 / 4])(ptr, arg);
    }

    if (ptr[0x78 / 4] != 0) {
        ((func_0203c7ac_cb2)ptr[0x78 / 4])(ptr, arg, ptr[0x84 / 4]);
    }
}
