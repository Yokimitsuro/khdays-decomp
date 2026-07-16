extern int data_ov025_020b574c[];
extern char data_ov025_020b4a78[];

void func_ov025_0208527c(int arg0)
{
    int index = data_ov025_020b574c[1];

    if (index != -1) {
        ((void (*)(int))*(int *)(*(char **)(data_ov025_020b4a78 + index * 8) + 8))(arg0);
    }
}
