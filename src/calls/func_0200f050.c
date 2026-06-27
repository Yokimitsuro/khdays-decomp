extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern void func_02001f10(int arg0);
extern int data_020464e0[];

void func_0200f050(void) {
    int *ptr;
    int zero;
    int mask;

    ptr = data_020464e0;
    zero = 0;
    while (1) {
        mask = OS_DisableInterrupts();
        if ((ptr[0x45] & 8) == 0) {
            do {
                func_02001f10(zero);
            } while ((ptr[0x45] & 8) == 0);
        }
        OS_RestoreInterrupts(mask);
        ((void (*)(int *))ptr[0x10])(ptr);
    }
}
