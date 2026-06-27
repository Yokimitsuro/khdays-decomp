extern void MIi_CpuSend32(const void *src, volatile void *dst, unsigned int size);

extern volatile int data_027e0078;
extern int *data_027e0074;

void func_01ff80b8(void) {
    while (data_027e0078) {
        ;
    }
    {
        int *list = data_027e0074;
        if (list[0] == 0) return;
        MIi_CpuSend32(list + 1, (volatile void *)0x04000400, (unsigned int)(list[0] << 2));
        data_027e0074[0] = 0;
    }
}
