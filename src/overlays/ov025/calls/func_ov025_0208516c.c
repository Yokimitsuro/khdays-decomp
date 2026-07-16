extern int data_ov025_020b574c[];
extern char data_ov025_020b4ab0[];

void func_ov025_0208516c(int arg0)
{
    int index = data_ov025_020b574c[0];

    if (index != -1) {
        ((void (*)(int))*(int *)(*(char **)(data_ov025_020b4ab0 + index * 8) + 4))(arg0);
    }
}
