/* Snapshot +0x6c into +0x64/+0x68, then dispatch via c634 choosing the callback by +0x74. */
extern int func_0203c634(int, int, void *);
extern int func_ov260_020ce8b0(int);
extern int func_ov260_020cec1c(int);
int func_ov260_020cebe4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int v = *(int *)(owner + 0x6c);
    *(int *)(owner + 0x64) = v;
    *(int *)(owner + 0x68) = v;
    return func_0203c634(param_1, *(signed char *)(param_1 + 0x20),
        *(int *)(owner + 0x74) < 5 ? (void *)&func_ov260_020ce8b0 : (void *)&func_ov260_020cec1c);
}
