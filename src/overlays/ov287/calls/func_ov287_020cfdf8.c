extern void func_0203c7e8();
extern void NNSi_FndDestroyDoubleList();
extern void func_ov107_020c68ec();

struct row8 { int a, b; };

void func_ov287_020cfdf8(int this_) {
    int i;
    func_0203c7e8(*(int *)(this_ + 0x384));
    for (i = 0; i < 2; i++) {
        int slot = ((struct row8 *)this_)[i + 120].a;
        if (slot) func_0203c7e8(slot);
    }
    NNSi_FndDestroyDoubleList(this_ + 0x398);
    func_ov107_020c68ec(this_);
}
