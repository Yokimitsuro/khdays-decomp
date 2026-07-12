/* Return +0x4ad0 of the ov000 global object when both it and the value are non-null, else 0. */
extern int data_ov000_0205ac24;
int func_ov000_0205328c(void) {
    int b = data_ov000_0205ac24;
    return (b != 0 && *(int *)(b + 0x4ad0) != 0) ? *(int *)(b + 0x4ad0) : 0;
}
