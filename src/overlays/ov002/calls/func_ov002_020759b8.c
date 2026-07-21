extern int func_02021980(int vm, unsigned short *pc);
extern int func_ov002_0206e3d0(int id, int kind, int value);
/* Script op: unpack id/kind from the opcode word, read the signed value operand, and apply it. */
int func_ov002_020759b8(int vm, int op) {
    unsigned int packed = *(unsigned int *)(op + 4);
    int v = func_02021980(vm, (unsigned short *)(op + 8));
    if (func_ov002_0206e3d0(packed & 0xffff,
                            (unsigned char)(unsigned short)(packed >> 0x10),
                            (short)v) != 0) {
        return 1;
    }
    return 0;
}
