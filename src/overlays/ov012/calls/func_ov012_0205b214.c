extern int data_ov012_0205cb20;
extern void func_ov024_02084df4();

void func_ov012_0205b214(int arg0, int arg1) {
    char *base = (char *)(data_ov012_0205cb20 + 0x8000);
    *(int *)(base + 0xbe4) = arg1;
    *(int *)(base + 0xbe8) = -1;
    *(unsigned char *)(base + 0xbe2) = (unsigned char)arg0;
    if (*(int *)(base + 0xbdc) != 1) return;
    *(int *)(base + 0xbdc) = 2;
    func_ov024_02084df4(0);
}
