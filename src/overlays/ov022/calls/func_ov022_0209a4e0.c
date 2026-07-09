extern void func_01fffe68(void);
void func_ov022_0209a4e0(int arg0) {
    *(void (**)(void))(arg0 + 0x24) = func_01fffe68;
    *(char *)(arg0 + 0x92) = 3;
}
