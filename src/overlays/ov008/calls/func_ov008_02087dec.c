extern int func_ov008_020882d8(void);
extern void func_ov008_02082bf4(void);
extern void func_ov008_020878c4(void);
extern void func_ov008_02087e14(void);

void (*func_ov008_02087dec(void))(void)
{
    void (*callback)(void);

    if (func_ov008_020882d8() != 0) {
        callback = func_ov008_02087e14;
    } else {
        callback = 0;
    }

    func_ov008_02082bf4();
    func_ov008_020878c4();

    return callback;
}
