extern void func_0203b9fc();
extern void func_0203c7ac();

struct bit0 { unsigned char b : 1; };

void func_ov240_020ce2ac(int this_) {
    func_0203b9fc(*(int *)(this_ + 0x388), 0,
                  *(signed char *)(this_ + 0x310),
                  ((struct bit0 *)(this_ + 0x311))->b);
    func_0203c7ac(*(int *)(this_ + 0x388), 0);
}
