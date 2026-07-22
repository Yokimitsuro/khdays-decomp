/* Script opcode: drive func_ov002_02073ed0 with three operands, the first
 * narrowed differently depending on the boot mode -- bit 2 of data_0204c240
 * takes the SIGNED high halfword, otherwise the unsigned low one. Reports 1. */
extern int func_02021980(void *self, void *arg);
extern void func_ov002_02073ed0(int a, int b, int c);

extern unsigned char data_0204c240;

int func_ov002_0207535c(void *self, char *args) {
    int a = func_02021980(self, args);
    int b = func_02021980(self, args + 8);
    int c = func_02021980(self, args + 0x10);
    int value;

    if (data_0204c240 & 4) {
        value = a >> 0x10;
    } else {
        value = (unsigned short)a;
    }

    func_ov002_02073ed0(value, b, c);
    return 1;
}
