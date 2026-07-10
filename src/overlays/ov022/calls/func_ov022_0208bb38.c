extern void func_ov022_0208b214(int arg0);
extern void func_ov022_02090070(int arg0);

void func_ov022_0208bb38(int arg0, int arg1, int arg2, int arg3) {
    int e = *(int *)(arg0 + *(int *)(arg0 + 0xc) * 4 + 0x18);
    int i = 0;
    int off;
    if ((int)*(unsigned char *)(e + 1) > 0) {
        off = 0;
        do {
            func_ov022_0208b214(*(int *)(e + 0x168) + off);
            i = i + 1;
            off = off + 0x150;
        } while (i < *(unsigned char *)(e + 1));
    }
    if (*(int *)(e + 0x170) != 0) func_ov022_02090070(arg0);
}
