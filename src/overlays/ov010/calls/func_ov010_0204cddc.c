extern int NNSi_FndGetCurrentRootHeap();
extern void func_02035f84();
extern void func_02035fb0();
extern void func_02035ffc();

void func_ov010_0204cddc(int arg0, int arg1, int arg2) {
    int heap = NNSi_FndGetCurrentRootHeap();
    func_02035f84(heap + 0x58);
    func_02035fb0(heap + 0x58, 0, arg0, arg1, arg2);
    func_02035ffc(heap + 0x58);
}
