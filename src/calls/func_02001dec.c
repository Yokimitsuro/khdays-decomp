extern int OS_DisableInterrupts();
extern void func_02001e0c(void *thread, int arg);
extern void *data_0204430c[];

void func_02001dec(void) {
    OS_DisableInterrupts();
    func_02001e0c(data_0204430c[0xa], 0);
}
