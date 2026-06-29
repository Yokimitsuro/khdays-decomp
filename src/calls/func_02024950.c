extern char data_02041fd4[];

int func_02024950(int index) {
    int (*callback)(void) = *(int (**)(void))(data_02041fd4 + index * 0x18);

    if (callback == 0) {
        return 0;
    }

    return callback();
}
