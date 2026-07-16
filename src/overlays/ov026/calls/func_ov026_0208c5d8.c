extern char *data_ov026_02091368;
extern void func_ov026_0208a2fc(void);
extern void func_ov026_0208a774(void);
extern void func_ov026_0208c598(void);
extern void func_ov026_0208cb0c(void);

void (*func_ov026_0208c5d8(void))(void)
{
    func_ov026_0208a2fc();
    func_ov026_0208a774();

    if (*(int *)(data_ov026_02091368 + 0xc56c) != 0) {
        return func_ov026_0208c598;
    }

    return func_ov026_0208cb0c;
}
