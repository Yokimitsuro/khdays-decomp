extern void func_ov030_020b4048(void *this, int arg);

void func_ov030_020b4000(char *this) {
    func_ov030_020b4048(this, 2);
    *(signed char *)(this + 0x12c) = 5;
    *(int *)(this + 0x130) = 0;
}
