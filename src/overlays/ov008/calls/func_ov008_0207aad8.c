extern char *data_ov008_02090f24;
extern void func_ov008_02079a20(void);
extern void func_ov008_0207ab08(void);

void (*func_ov008_0207aad8(void))(void)
{
    void (*callback)(void) = 0;

    func_ov008_02079a20();
    if (*(int *)(data_ov008_02090f24 + 0x49c) == 0) {
        callback = func_ov008_0207ab08;
    }

    return callback;
}
