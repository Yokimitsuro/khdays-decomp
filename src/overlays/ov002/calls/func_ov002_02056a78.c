/* Forward the table entry (*global)[param_1] + 0x220 (and param_2) to func_ov002_020593b4. */
extern int func_ov002_020593b4(int entry, int arg);
extern int data_ov002_0207f614;

int func_ov002_02056a78(int param_1, int param_2) {
    return func_ov002_020593b4(*(int *)(*(int *)&data_ov002_0207f614 + param_1 * 4 + 0x220), param_2);
}
