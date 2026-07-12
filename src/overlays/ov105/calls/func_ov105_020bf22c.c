/* Store param_1 and the u16 param_2 into the global record at data_ov105_020c0580. */
extern int data_ov105_020c0580;
void func_ov105_020bf22c(int param_1, int param_2) {
    *(int *)&data_ov105_020c0580 = param_1;
    *(unsigned short *)((char *)&data_ov105_020c0580 + 4) = (unsigned short)param_2;
}
