extern void func_ov016_020821f8(void *self, int value, int flag);

void func_ov016_02082294(char *self, char *arg1) {
    if ((unsigned char)arg1[0] == 1) {
        func_ov016_020821f8(self, *(int *)(arg1 + 4), 1);
    }
    self[0x2bc] = 0;
}
