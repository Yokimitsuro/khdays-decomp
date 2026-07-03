extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov046_020b3290(int a);
extern void func_ov046_020b3974(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov046_020b3234(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov046_020b3290(param);
    func_ov046_020b3974(obj);
    func_ov022_020a4798(obj, 0x48, 0xd6);
    return (void *)func_ov022_0209fb24;
}
