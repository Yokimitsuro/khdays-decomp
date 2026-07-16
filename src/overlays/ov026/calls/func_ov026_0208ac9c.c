extern int func_ov026_0208b188(void);
extern void func_ov026_02085aa4(void);
extern void func_ov026_0208a774(void);
extern void func_ov026_0208acc4(void);

void (*func_ov026_0208ac9c(void))(void)
{
    void (*callback)(void);

    if (func_ov026_0208b188() != 0) {
        callback = func_ov026_0208acc4;
    } else {
        callback = 0;
    }

    func_ov026_02085aa4();
    func_ov026_0208a774();

    return callback;
}
