extern int func_ov002_0206fb84(int kind, int *out);

int func_ov002_0206ec2c(void) {
    int out;
    return func_ov002_0206fb84(4, &out) != 0xffff;
}
