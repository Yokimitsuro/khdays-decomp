extern unsigned char *data_0204c234;
extern int func_02032928(void *ptr, int arg);
extern void func_0201c608(void *ptr, void *arg1, int arg2);

void func_02033b24(void *ptr, int arg) {
    if (ptr == 0) {
        ptr = *(void **)(data_0204c234 + 0x9c);
    }

    if (func_02032928(ptr, arg) == 0) {
        return;
    }

    func_0201c608(data_0204c234 + 0xb44c8, ptr, arg);
}
