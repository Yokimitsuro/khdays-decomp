extern void func_ov107_020c887c(int *self, int arg);

typedef void (*func_ov237_020ccfb4_cb)(int *target, int arg);

void func_ov237_020ccfb4(int *self, int arg) {
    int *target = (int *)self[0x4a4 / 4];
    if (target != 0 && target[0x1f0 / 4] != 0) {
        ((func_ov237_020ccfb4_cb)target[0x1f0 / 4])(target, arg);
    }
    func_ov107_020c887c(self, arg);
}
