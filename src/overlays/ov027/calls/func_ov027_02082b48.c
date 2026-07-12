/* Read the chained field at (*(&data+4))+0x24. */
extern int data_ov027_02084360;
int func_ov027_02082b48(void) {
    return *(int *)(*(int *)((char *)&data_ov027_02084360 + 4) + 0x24);
}
