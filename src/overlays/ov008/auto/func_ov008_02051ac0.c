struct ov008_ptr_slot {
    char *ptr;
    int _pad;
};

extern int data_ov008_02090f0c[];
extern struct ov008_ptr_slot data_ov008_0209009c[];
int func_ov008_02051ac0(void)
{
    return *(int *)(data_ov008_0209009c[data_ov008_02090f0c[0]].ptr + 0xc);
}
