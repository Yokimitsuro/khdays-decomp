/* Return +0x4bc4 of the ov000 global object when both it and the value are non-null, else 0. */
extern int data_ov000_0205ac28;
int func_ov000_020548e0(void) {
    int b = data_ov000_0205ac28;
    return (b != 0 && *(int *)(b + 0x4bc4) != 0) ? *(int *)(b + 0x4bc4) : 0;
}
