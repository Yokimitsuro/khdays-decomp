extern int data_02047364[];
extern void *data_020423f4;
extern void *data_020423f8;
extern void func_0201133c(int value);
extern void func_020111c0(void);
extern void func_020112fc(void);

void func_02011174(int value, int install_callbacks) {
    data_02047364[2] = value;
    func_0201133c(value);

    if (install_callbacks != 0) {
        data_020423f4 = func_020111c0;
        data_020423f8 = func_020112fc;
    }
}
