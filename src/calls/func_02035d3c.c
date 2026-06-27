extern int MI_CpuCopy8();

extern char data_0204c6a0[];
extern char data_0204c7a4[];
extern char data_0204c6b4[];
extern char data_0204c7b8[];
extern char data_0204c714[];
extern char data_0204c818[];

void func_02035d3c(void) {
    MI_CpuCopy8(data_0204c6a0, data_0204c7a4, 0x14);
    MI_CpuCopy8(data_0204c6b4, data_0204c7b8, 0x60);
    MI_CpuCopy8(data_0204c714, data_0204c818, 0x1e);
}
