extern volatile int data_027e0078;

void FSi_WaitForCardThread(int unused) {
    (void)unused;
    while (data_027e0078 != 0) {}
}
