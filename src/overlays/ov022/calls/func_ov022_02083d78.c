extern int *data_ov022_020b2e60;
int func_ov022_02083d78(void) {
    if (data_ov022_020b2e60 == 0) return 0;
    return (int)(*(unsigned short *)data_ov022_020b2e60 & 4) <= 0;
}
