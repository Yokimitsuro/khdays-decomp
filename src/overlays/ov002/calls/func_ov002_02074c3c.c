extern int func_02021980(int a, char *b);
extern void func_ov002_0206ac74(int a, int b, int c);
extern int func_02023534(void);
extern void func_0202354c(int a);

/* Registers the three sub-emitters of a field effect and starts it. */
int func_ov002_02074c3c(int scene, char *desc) {
    int a = func_02021980(scene, desc);
    int b = func_02021980(scene, desc + 8);
    func_ov002_0206ac74(a, b, func_02021980(scene, desc + 0x10));
    if (func_02023534() == 0) {
        func_0202354c(1);
    }
    return 1;
}
