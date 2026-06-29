extern void func_02014024(void *ptr, int word0, int arg1, int arg2, int arg3, unsigned short arg4);

void func_02030194(int *ptr, int arg1, int arg2, int arg3, unsigned short arg4) {
    func_02014024((char *)ptr[6] + 8, ptr[0], arg1, arg2, arg3, arg4);
}
