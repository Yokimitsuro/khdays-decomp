extern void func_0202a7dc();
extern void func_0203d194();
extern void NNSi_FndDestroyDoubleList();
extern void func_0203c900();

void func_0203b968(int this_) {
    func_0202a7dc(*(int *)(this_ + 0x88));
    func_0203d194(*(int *)(this_ + 0x88));
    *(int *)(this_ + 0x88) = 0;
    if (*(int *)(this_ + 0x90) != 0) {
        NNSi_FndDestroyDoubleList(*(int *)(this_ + 0x90));
        func_0203d194(*(int *)(this_ + 0x90));
    }
    func_0203c900(this_);
}
