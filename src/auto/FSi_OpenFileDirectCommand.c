int FSi_OpenFileDirectCommand(int *f) {
    f[9] = f[12];
    f[11] = f[12];
    f[10] = f[13];
    f[8] = f[14];
    return 0;
}
