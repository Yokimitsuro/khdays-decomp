extern unsigned char *data_0204c234;
extern void func_02019e9c(void *ptr, int arg);

void func_02032d6c(int arg) {
    unsigned char *base = data_0204c234;

    *(short *)(base + 0xb46f6) = -1;
    func_02019e9c(base + 0xb44c4, arg);
    *(int *)(base + 0xb4700) = arg;
    *(unsigned char *)(base + 0xb46fc) = 4;
}
