extern int func_ov025_02084a8c();
extern int func_ov025_02088b1c();

void func_ov025_020ae6c0(int arg0) {
    int buf[2];
    func_ov025_02088b1c(func_ov025_02084a8c(arg0), (int)buf);
    if (*(unsigned short *)((char *)buf + 4) != 1) {
        *(int *)(arg0 + 0x10) = 0;
    }
}
