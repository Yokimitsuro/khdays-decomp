extern int func_02021980(int vm, unsigned short *pc);
extern void func_ov002_02073fb0(unsigned int value, int arg);
extern unsigned char data_0204c240;
/* Script op: read a packed value and an argument; take the value's high half when global flag
 * bit 2 is set, else its low half, then dispatch. */
int func_ov002_020753a0(int vm, unsigned short *pc) {
    unsigned int v = func_02021980(vm, pc);
    int arg = func_02021980(vm, pc + 4);
    if ((data_0204c240 & 4) != 0) {
        v = (int)v >> 0x10;
    } else {
        v = v & 0xffff;
    }
    func_ov002_02073fb0(v, arg);
    return 1;
}
