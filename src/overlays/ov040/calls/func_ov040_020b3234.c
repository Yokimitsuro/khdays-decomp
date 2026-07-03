extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov040_020b327c(int a);
extern void func_ov040_020b3868(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov040_020b3234(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov040_020b327c(param);
    func_ov040_020b3868(obj);
    func_ov022_020a4798(obj, 0x4b, 0xce);
    return (void *)func_ov022_0209fb24;
}
