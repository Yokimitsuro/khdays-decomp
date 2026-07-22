extern int data_ov002_0207f9fc;
extern void (*data_ov002_0207eed8[])(void);

int func_ov002_020678c4(void) {
    int ctx = *(int *)&data_ov002_0207f9fc;
    void (*handler)(void);

    if (*(int *)(ctx + 0x20) != 0) {
        handler = data_ov002_0207eed8[*(int *)(ctx + 0x28)];
        if (handler != 0) {
            handler();
        }
    }
    return 0;
}
