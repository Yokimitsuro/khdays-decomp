extern void func_ov146_020ce298(int a, int b);
extern void func_0203c634(int self, int index, void *cb);
struct hw60 { unsigned short lo:8, hi:8; };
void func_ov146_020ccdf4(int self) {
    int obj = *(int *)(self + 4);
    if ((((struct hw60 *)(*(int *)obj + 0x60))->lo & 1) == 0) {
        return;
    }
    *(int *)(obj + 0x58) = 1;
    func_ov146_020ce298(*(int *)(obj + 8), 1);
    *(signed char *)(*(int *)obj + 0x1c7) = *(signed char *)(*(int *)obj + 0x1c9);
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
