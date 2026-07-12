/* Twin of func_ov008_02050f40; the handle slot is at global+0x96b8. */
extern int data_ov008_02090f04;

int func_ov008_02050f84(int param_1) {
    int g = *(int *)((char *)&data_ov008_02090f04 + 4);
    int handle = *(int *)(g + 0x96b8);
    if (handle == 0) return 0;
    return (((handle + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (param_1 & 0x1ff);
}
