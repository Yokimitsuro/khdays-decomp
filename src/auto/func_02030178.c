void func_02030178(int this_, int arg1) {
    int obj = *(int *)(this_ + 0x18);
    (*(void (**)(int, int))(*(int *)(obj + 0x1c) + 4))(obj + 8, arg1);
}
