/* Snapshot the result screen into the shared report block: the caller's code
 * plus the two signed halfwords at the head of the result context (root +
 * 0x8ba8), and two pointers back into the root for the reader to follow. */
extern char *data_ov002_0207fa00;
extern short data_0204c270[];
extern int data_0204c2f0[];

void func_ov002_0206a3d8(int code) {
    char *root = data_ov002_0207fa00;
    short *result = (short *)(root + 0x8ba8);

    data_0204c270[0] = (short)code;
    data_0204c270[1] = result[0];
    data_0204c270[2] = result[1];
    data_0204c2f0[2] = (int)(root + 8);
    data_0204c2f0[3] = (int)(root + 0x859c);
}
