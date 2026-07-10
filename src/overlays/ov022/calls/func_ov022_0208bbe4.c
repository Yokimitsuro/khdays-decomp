extern void func_ov022_02090070(int arg0, int arg1, int arg2, int arg3);
extern void func_ov022_0208b2a8(int arg0);

void func_ov022_0208bbe4(int arg0, int arg1, int arg2, int arg3) {
    int e = *(int *)(arg0 + *(int *)(arg0 + 0xc) * 4 + 0x18);
    int i;
    int off;
    if (*(int *)(e + 0x170) != 0) {
        func_ov022_02090070(arg0, *(int *)(e + 0x170), arg2, arg3);
    }
    i = 0;
    if ((int)*(unsigned char *)(e + 1) <= 0) return;
    off = 0;
    do {
        func_ov022_0208b2a8(*(int *)(e + 0x168) + off);
        i = i + 1;
        off = off + 0x150;
    } while (i < *(unsigned char *)(e + 1));
}
