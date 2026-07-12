/* Look up an entry in the table at data_ov002_0207dcc0, indexed by the count at
 * (*global)+0x134. */
extern int data_ov002_0207f614;
extern int data_ov002_0207dcc0;

int func_ov002_020575b0(void) {
    int idx = *(int *)(*(int *)&data_ov002_0207f614 + 0x134);
    return ((int *)&data_ov002_0207dcc0)[idx];
}
