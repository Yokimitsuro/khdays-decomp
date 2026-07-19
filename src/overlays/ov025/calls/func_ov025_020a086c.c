extern char *func_ov025_02084afc(void);
extern void func_ov025_0209e8c4(void);
extern void func_ov025_0209e93c(void);
extern int func_ov025_02084a50(void);
extern int func_ov025_02084a7c(void);
extern void func_ov025_0209eb28(void);
extern void func_ov025_0209ebb4(void);
extern void func_ov025_0209eea8(void);
extern void func_ov025_0209f430(void);
extern void func_ov025_0209ef60(void);
extern void func_ov025_0209f860(void);
extern void func_ov025_020a0428(void);
extern void func_ov025_0209f548(int page);
extern void func_ov025_020a076c(void);

/* Brings the panel screen up: caches the two active objects and initialises every widget. */
int func_ov025_020a086c(void) {
    char *self = func_ov025_02084afc();
    func_ov025_0209e8c4();
    func_ov025_0209e93c();
    *(int *)(self + 0xb4) = func_ov025_02084a50();
    *(int *)(self + 0xb8) = func_ov025_02084a7c();
    func_ov025_0209eb28();
    func_ov025_0209ebb4();
    func_ov025_0209eea8();
    func_ov025_0209f430();
    func_ov025_0209ef60();
    func_ov025_0209f860();
    func_ov025_020a0428();
    func_ov025_0209f548(*(short *)(self + 4));
    func_ov025_020a076c();
    return 1;
}
