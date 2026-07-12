/* Swap the two shared global words. */
extern int data_0204c024;
extern int data_0204c02c;
void func_ov023_02082c5c(void) {
    int tmp = data_0204c024;
    data_0204c024 = data_0204c02c;
    data_0204c02c = tmp;
}
