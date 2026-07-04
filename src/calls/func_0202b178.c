extern void func_0202a634();

struct vec3 { int x, y, z; };

int func_0202b178(int this_, int arg1, int arg2, int arg3) {
    if (arg1 != 0) {
        *(int *)this_ &= ~0x20;
        func_0202a634(this_ + 4, arg1, arg2, arg3);
        if (*(int *)this_ & 8) {
            *(struct vec3 *)(this_ + 0xa8) = *(struct vec3 *)(this_ + 0x13c);
        }
    }
    return 1;
}
