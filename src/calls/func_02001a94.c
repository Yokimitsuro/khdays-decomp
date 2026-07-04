extern char data_0204430c[];

void func_02001a94(int target) {
    int prev = 0;
    int cur = *(int *)(data_0204430c + 0x2c);
    while (cur != 0 && cur != target) {
        prev = cur;
        cur = *(int *)(cur + 0x68);
    }
    if (prev == 0) {
        *(int *)(data_0204430c + 0x2c) = *(int *)(target + 0x68);
    } else {
        *(int *)(prev + 0x68) = *(int *)(target + 0x68);
    }
}
