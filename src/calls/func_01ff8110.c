extern volatile int data_027e0078;

void func_01ff8110(int unused) {
    (void)unused;
    while (data_027e0078 != 0) {}
}
