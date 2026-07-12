/*
 * Claim an entry slot: if the id word at (*global + 0x8ba8)+0xc is still -1
 * (unassigned), store param_1 into it.
 */
extern int data_ov002_0207fa00;

void func_ov002_0206ba28(int param_1) {
    int *entry = (int *)(*(int *)&data_ov002_0207fa00 + 0x8ba8);

    if (entry[3] == -1) {
        entry[3] = param_1;
    }
}
