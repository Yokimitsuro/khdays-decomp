extern void func_0202e760(void *ptr);
extern void func_0202e620(void *ptr);
extern unsigned char data_0204c214[];

int func_0202e9b8(void *ptr) {
    if (data_0204c214[1] != 0) {
        unsigned char value;

        if (data_0204c214[0] != 0) {
            func_0202e760(ptr);
        } else {
            func_0202e620(ptr);
        }

        data_0204c214[1] = 0;
        value = data_0204c214[0];
        data_0204c214[0] = value == 0;
    }

    return data_0204c214[0];
}
