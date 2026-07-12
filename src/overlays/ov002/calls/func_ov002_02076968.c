/* Forward the entry at *(global+4) + 0x200 + param_1*4 (and param_2) to func_02025640. */
extern int func_02025640(int entry, int arg);
extern int data_ov002_0207fa20;
int func_ov002_02076968(int param_1, int param_2) {
    return func_02025640(*(int *)((char *)&data_ov002_0207fa20 + 4) + 0x200 + param_1 * 4, param_2);
}
