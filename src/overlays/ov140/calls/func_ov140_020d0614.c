extern int func_01fff948();

int func_ov140_020d0614(int this_, int arg1) {
    int *s = *(int **)(this_ + 4);
    int val = *(int *)(*(int *)(*s + 4) + 0x7c);
    if (val == 0) goto ret0;
    if (func_01fff948(val, *(int *)((char *)s + 0x4c), arg1, 0x10) != 0) return 1;
ret0:
    return 0;
}
