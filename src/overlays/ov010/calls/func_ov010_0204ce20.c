extern int NNSi_FndGetCurrentRootHeap();
extern void func_0203602c();
extern void func_0201e374();
extern void func_0201e3cc();

struct bf70 { unsigned int _pad : 2; unsigned int b : 1; };

int func_ov010_0204ce20(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    int v;
    int s;
    func_0203602c(obj + 0x58, &v);
    s = v >> 12;
    func_0201e374(s);
    func_0201e3cc(s);
    return ((struct bf70 *)(obj + 0x70))->b;
}
