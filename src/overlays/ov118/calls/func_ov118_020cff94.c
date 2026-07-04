extern void func_ov118_020cfe08();
extern void func_ov107_020c7ca4();

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov118_020cff94(int this_) {
    unsigned int lo = ((struct hw60 *)(this_ + 0x60))->lo;
    if ((lo & 0x80) || !(lo & 1)) {
        func_ov118_020cfe08(this_);
    }
    func_ov107_020c7ca4(this_);
}
