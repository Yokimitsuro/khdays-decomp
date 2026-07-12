/* Report whether the stride-6 table byte at row param_1, column param_2 is not 0xff. */
extern unsigned char data_ov107_020cb6a4[];
int func_ov107_020c0770(int param_1, int param_2) {
    unsigned char *row = data_ov107_020cb6a4 + param_1 * 6;
    return row[param_2] != 0xff;
}
