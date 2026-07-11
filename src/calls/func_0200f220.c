extern void OS_Terminate(void);
extern void func_0200f284(void);
extern int data_02046d40;

void func_0200f220(int arg0, int arg1) {
    if ((arg1 & 0x3f) == 0x11) {
        if (data_02046d40 != 0) return;
        data_02046d40 = 1;
        {
            int (*fn)(void) = *(int (**)(void))((char *)&data_02046d40 + 4);
            int r = 1;
            if (fn != 0) r = fn();
            if (r != 0) func_0200f284();
        }
    } else {
        OS_Terminate();
    }
}
