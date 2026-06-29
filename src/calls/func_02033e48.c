extern unsigned char *data_0204c234;
extern void func_02019e9c(void *ptr, int value);
extern void func_02032a7c(void *ptr);

void func_02033e48(unsigned int arg) {
    unsigned char *entry = data_0204c234 + 0xb44e4 + (arg >> 24) * 0x20;

    if (*(unsigned short *)(entry + 0x14) == 0) {
        return;
    }

    if (*(unsigned int *)(entry + 0x18) != (arg & 0x00ffffff)) {
        return;
    }

    func_02019e9c(entry + 0x1c, 0);
    func_02032a7c(entry);
}
