/* Set the global word at +0x95d0 to 0x20 for param_1==0 or 0x40 for param_1==1;
 * other values do nothing. */
extern int data_ov008_02090f04;

void func_ov008_02050c8c(int param_1) {
    switch (param_1) {
    case 0:
        *(int *)(*(int *)((char *)&data_ov008_02090f04 + 4) + 0x95d0) = 0x20;
        break;
    case 1:
        *(int *)(*(int *)((char *)&data_ov008_02090f04 + 4) + 0x95d0) = 0x40;
        break;
    }
}
