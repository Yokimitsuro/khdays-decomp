extern void func_0202a634(int a, int b, int c, int d);
extern void func_ov100_020bbd0c(int p);
extern int data_ov100_020bc194;

void func_ov100_020bb6d0(int this_) {
    char *a = (char *)(this_ + 0x2000);
    char *b = (char *)(this_ + 0x2df0);
    *(unsigned char *)(a + 0xdf0) = 0;
    *(int *)(b + 0x114) = 0;
    func_0202a634((int)(b + 4), (int)&data_ov100_020bc194, 1, *(unsigned char *)(this_ + 9) + 7);
    func_ov100_020bbd0c(this_);
}
