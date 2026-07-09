extern int func_ov025_020ae068();
extern int data_0204c18c;

void func_ov025_020aeb44(int arg0) {
    if (*(int *)(arg0 + 0xc) != 0 || *(int *)(arg0 + 0x10) != 0) {
        return;
    }
    if ((*(unsigned short *)&data_0204c18c & 0xf0) != 0x20) {
        return;
    }
    func_ov025_020ae068(arg0, -1);
}
