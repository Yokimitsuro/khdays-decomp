extern void func_ov107_020c9264();
extern void func_ov240_020ce8d4();
extern void func_0203c634();
extern void func_ov240_020cf474();

void func_ov240_020cf424(int this_) {
    int node = *(int *)(this_ + 4);
    func_ov107_020c9264(*(int *)node, 7, 0);
    func_ov240_020ce8d4(*(int *)node, 2);
    *(int *)(node + 0x38) = 0;
    *(unsigned char *)(node + 0x3e) = 0;
    *(unsigned char *)(node + 0x3c) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov240_020cf474);
}
