extern int func_02023eb4();
extern int func_0203c634();

void func_ov137_020ccf0c(unsigned char *obj) {
    unsigned char *mid = *(unsigned char **)(obj + 4);
    unsigned char *inner = *(unsigned char **)(mid + 0);
    if (((unsigned char)*(unsigned short *)(inner + 0x60)) & 1) {
        int base = *(int *)(inner + 0x224);
        int diff = *(int *)(inner + 0x228) - base;
        if (diff < 0) diff = -diff;
        *(int *)(mid + 0x44) = base + func_02023eb4(diff + 1);
        {
            unsigned char *in2 = *(unsigned char **)(mid + 0);
            *(signed char *)(in2 + 0x1c7) = *(signed char *)(in2 + 0x1c9);
        }
        func_0203c634(obj, *(signed char *)(obj + 0x20), 0);
    }
}
