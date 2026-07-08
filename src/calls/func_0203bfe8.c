extern int *func_01fffd70();
extern void func_0203c83c();
extern void func_01fffd0c();
extern int *func_01fffd8c();
int func_0203bfe8(int param_1, int *param_2, unsigned int param_3)
{
    int *node;
    int i;
    if (param_2 != 0) {
        i = 0;
        node = func_01fffd70(param_1 + 0x88);
        while (node != 0) {
            if ((int *)*node == param_2) {
                func_0203c83c(param_2, 0);
                func_01fffd0c(param_1 + 0x88, (int)node);
                return i;
            }
            i++;
            node = func_01fffd8c(param_1 + 0x88);
        }
    }
    return -1;
}
