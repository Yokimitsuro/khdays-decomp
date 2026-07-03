extern void func_0202a634(int a, void *b, int c, int d);
extern int data_ov030_020b5998[];
void func_ov030_020b3e9c(int this) {
    int obj = *(int *)(this + 0xdb4);
    int i = 0;
    int base = this + 0x234;
    do {
        func_0202a634(base, data_ov030_020b5998, 1, ((unsigned char *)obj)[9] + 7);
        *(unsigned char *)(base + 0x12d) = i;
        *(unsigned char *)(base + 0x12c) = 0;
        base += 0x170;
        i++;
    } while (i < 8);
}
