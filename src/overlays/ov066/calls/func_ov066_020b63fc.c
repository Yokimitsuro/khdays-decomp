extern int func_02033d0c(int a, int b, int c, int d);

typedef struct { unsigned char b0 : 1; } Flags;

int func_ov066_020b63fc(int owner, int node) {
    int obj = *(int *)(owner + 8);
    int *hdr = *(int **)(node + 0x138);
    int loud = 0;
    *(signed char *)(node + 2) = 4;
    *(int *)(node + 4) = 0x3000;
    if (*hdr & 0x200) loud = 1;
    if (((Flags *)(obj + 0x694))->b0) {
        func_02033d0c(0xd4, loud, node + 0xcc, 0);
    }
    return 0;
}
