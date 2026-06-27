extern void OS_Terminate(void);
extern unsigned short data_02044694;

void func_020038e8(int unused, int status) {
    if ((unsigned int)((status & 0x7f00) << 8) >> 16 == 0x10) {
        data_02044694 = 1;
        return;
    }
    OS_Terminate();
}
