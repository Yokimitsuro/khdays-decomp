extern int func_02021980(int arg);
extern int func_02024fd4(void *arg0);

int func_02022544(int param_1) {
    int idx = func_02021980(param_1);
    void *entry = *(void **)(*(int *)(param_1 + 0x128) + idx * 4 + 0x48c);
    if (entry != 0) {
        func_02024fd4(entry);
        *(void **)(*(int *)(param_1 + 0x128) + idx * 4 + 0x48c) = 0;
    }
    return 1;
}
