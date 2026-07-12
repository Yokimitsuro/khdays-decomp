/* Spawn a child object via func_0203c5c0 (callbacks ov210_020d40a8 and ov210_020d4078), link it
 * back to this object and return it. */
extern int func_0203c5c0(int a, int b, int c, void *cb, void *cb2, int *out);
extern void func_ov282_020d40bc(int);
extern void func_ov282_020d408c(int);
int func_ov282_020d4040(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x4c, (void *)&func_ov282_020d408c,
                  (void *)&func_ov282_020d40bc, &obj);
    *(int *)obj = param_1;
    return obj;
}
