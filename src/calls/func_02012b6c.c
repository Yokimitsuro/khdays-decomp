extern int data_02041a04;

int func_02012b6c(int arg0) {
    unsigned int v = *(unsigned short *)((char *)&data_02041a04 + arg0 * 2);
    if (v == 0) return arg0;
    if ((*(unsigned short *)(v + 0x4000000) & 0x2000) != 0) arg0 += 2;
    return arg0;
}
