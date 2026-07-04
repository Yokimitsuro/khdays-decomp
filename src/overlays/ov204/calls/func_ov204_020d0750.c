extern int func_01fff948();

int func_ov204_020d0750(int this_, int arg1) {
    int *s = *(int **)(this_ + 4);
    int val = *(int *)(*(int *)(*s + 4) + 0x7c);
    if (val == 0) goto ret0;
    if (func_01fff948(val, *(int *)((char *)s + 0x24), arg1, 0x800) != 0) return 1;
ret0:
    return 0;
}
