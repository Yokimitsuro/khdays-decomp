extern void func_ov022_0208a134(unsigned int arg0);
void func_ov022_02093c0c(int arg0) {
    if (*(unsigned char *)(arg0 + 1) != 0) return;
    *(char *)(arg0 + 1) = 4;
    func_ov022_0208a134(*(unsigned char *)(*(int *)(arg0 + 0x4d8) + 9));
}
