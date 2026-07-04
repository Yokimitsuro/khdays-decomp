extern char data_0204bbfc[];
extern void func_0201e9e4();
extern void func_0201ea28();
extern void func_0201e9fc();
extern void func_0201ea40();

void func_0201f390(int arg0) {
    if (arg0 == 0) {
        *(void **)(data_0204bbfc + 0xc) = (void *)func_0201e9fc;
        *(void **)(data_0204bbfc + 0x10) = (void *)func_0201ea40;
    } else {
        *(void **)(data_0204bbfc + 0xc) = (void *)func_0201e9e4;
        *(void **)(data_0204bbfc + 0x10) = (void *)func_0201ea28;
    }
}
