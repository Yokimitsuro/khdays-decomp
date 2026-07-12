/* Unless either busy byte at *(child+4)+0xad or *(child+8)+0xad is set, invoke func_0203c640. */
extern void func_0203c640(int a);
void func_ov236_020d6250(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0 ||
        *(unsigned char *)(*(int *)(child + 8) + 0xad) != 0) return;
    func_0203c640(param_1);
}
