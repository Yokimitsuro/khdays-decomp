extern unsigned char data_0204a320[];
extern void func_0201a5b8();

void func_02019f6c(int arg0) {
    int i = 0;
    unsigned char *entry = data_0204a320;
    do {
        if (entry[0x2c] != 0) {
            func_0201a5b8(entry, arg0);
        }
        i++;
        entry += 0x44;
    } while (i < 0x10);
}
