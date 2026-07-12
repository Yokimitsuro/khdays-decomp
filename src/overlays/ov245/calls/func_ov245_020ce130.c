/* Run 020cce08 on the object, then dispatch via c634. */
extern int func_0203c634(int, int, void *);
extern int func_ov245_020cce08(int);
extern int func_ov245_020ce15c(int);
int func_ov245_020ce130(int param_1) {
    func_ov245_020cce08(*(int *)(*(int *)(param_1 + 4)));
    return func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov245_020ce15c);
}
