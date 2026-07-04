extern int func_02034014();
extern int data_ov011_0205e960;
extern void func_ov011_0205cb18();

void *func_ov011_0205ae14(void) {
    if (func_02034014(0) != 0) return 0;
    *(int *)(*(int *)((char *)&data_ov011_0205e960 + 4) + 4) = 5;
    return (void *)func_ov011_0205cb18;
}
