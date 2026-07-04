extern void *func_01fffd70();
extern void func_0203c424();
extern void NNSi_FndDestroyDoubleList();
extern void func_0203d194();

void func_0203c468(int this_) {
    void *r = func_01fffd70(this_);
    while (r != 0) {
        func_0203c424(this_, (int)r);
        r = func_01fffd70(this_);
    }
    NNSi_FndDestroyDoubleList(this_);
    func_0203d194(this_);
}
