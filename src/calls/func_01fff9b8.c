extern void func_01fffa60();
extern int data_0204c22c;

void func_01fff9b8(int arg0) {
    if (data_0204c22c == 0) return;
    if (*(unsigned short *)(arg0 + 2) != 0) return;
    if (*(int *)(arg0 + 0xc) == 0) return;
    func_01fffa60(*(int *)(arg0 + 0xc),
                  *(unsigned short *)(arg0 + 0x10),
                  *(unsigned short *)(arg0 + 0x12) + 1,
                  1);
}
