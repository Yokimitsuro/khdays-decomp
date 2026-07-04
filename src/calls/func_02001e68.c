extern char data_0204430c[];
extern int OS_DisableInterrupts();
extern void func_02001ea0();

void func_02001e68(int arg0) {
    int base = *(int *)(*(int *)(data_0204430c + 8));
    void (*cb)(int) = *(void (**)(int))(base + 0xb4);
    if (cb != 0) {
        *(int *)(base + 0xb4) = 0;
        cb(arg0);
        OS_DisableInterrupts();
    }
    func_02001ea0();
}
