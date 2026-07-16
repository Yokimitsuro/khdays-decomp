/* func_ov008_020559c0 -- initialise a tracker node and append it to the owner's list.
 * Stores the four bytes at node+0x1c..0x1f and the user word at node+0x24; resolves the bound tag
 * (node+0x28), where 0xffff means "no tag" -> 0. */
extern int  func_ov008_02055808(int owner, unsigned int tag);
extern void NNS_FndAppendListObject(void *list, void *obj);

void func_ov008_020559c0(int *param_1, int param_2, unsigned char param_3, unsigned char param_4,
                         unsigned char param_5, unsigned char param_6, unsigned short param_7,
                         int param_8) {
    int entry;
    *(unsigned char *)(param_2 + 0x1c) = param_3;
    *(unsigned char *)(param_2 + 0x1d) = param_4;
    *(unsigned char *)(param_2 + 0x1e) = param_5;
    *(unsigned char *)(param_2 + 0x1f) = param_6;
    *(int *)(param_2 + 0x24) = param_8;
    if (param_7 == 0xffff) {
        entry = 0;
    } else {
        entry = func_ov008_02055808((int)param_1, param_7);
    }
    *(int *)(param_2 + 0x28) = entry;
    NNS_FndAppendListObject(param_1, (void *)param_2);
}
