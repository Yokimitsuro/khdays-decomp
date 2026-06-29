typedef void (*func_02025420_cb)(void *ptr, unsigned int arg1, unsigned int arg2);

extern func_02025420_cb data_0204bc0c;

void func_02025420(unsigned char *ptr) {
    data_0204bc0c(ptr + *(int *)(ptr + 0x38),
                  (*(unsigned int *)(ptr + 0x2c) << 16) >> 13,
                  *(unsigned short *)(ptr + 0x30) << 3);
    *(unsigned short *)(ptr + 0x32) |= 1;
}
