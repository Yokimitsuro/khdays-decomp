/* If the ov000 global object exists, store a u16 at +0x1c. */
extern int data_ov000_0205ac28;
void func_ov000_020548c8(short param_1) {
    if (data_ov000_0205ac28 != 0) *(short *)(data_ov000_0205ac28 + 0x1c) = param_1;
}
