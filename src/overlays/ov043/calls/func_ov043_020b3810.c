/* Clear the +0x2d34 byte of the sub-block and tail-call 0202a7dc. */
extern int func_0202a7dc(int);
int func_ov043_020b3810(int param_1) {
    int p = param_1 + 0x2c2c;
    *(unsigned char *)(p + 0x108) = 0;
    return func_0202a7dc(p);
}
