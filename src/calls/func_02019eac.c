extern unsigned char data_0204a760[];
extern unsigned char data_0204a320[];
extern void func_0201a5b8(void *ptr, int arg);

void func_02019eac(int index, int arg) {
    int i = 0;
    unsigned char *entry = data_0204a320;
    int value = arg;
    unsigned char *target = data_0204a760 + index * 0x24;

    for (; i < 0x10; i++) {
        if (entry[0x2c] != 0 && *(unsigned char **)(entry + 4) == target) {
            func_0201a5b8(entry, value);
        }

        entry += 0x44;
    }
}
