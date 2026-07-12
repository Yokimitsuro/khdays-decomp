/* Return the signed halfword at (*global)+2 when status bit 1 is set, else -1. */
extern int data_ov002_0207fa04;

int func_ov002_0206eb40(void) {
    int base = *(int *)&data_ov002_0207fa04;
    int flag = *(unsigned short *)base & 2;
    if (flag > 0) {
        return *(short *)(base + 2);
    }
    return -1;
}
