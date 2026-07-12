/* Return bit 2 (mask 4) of the chained flag word at (*(&data+4))+0x1c. */
extern int data_ov027_02084360;
int func_ov027_02082b38(void) {
    return *(int *)(*(int *)((char *)&data_ov027_02084360 + 4) + 0x1c) & 4;
}
