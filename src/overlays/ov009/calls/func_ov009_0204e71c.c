extern int data_ov009_020563ec[];
extern char data_ov009_020562dc[];

void func_ov009_0204e71c(int arg0)
{
    int index = data_ov009_020563ec[0];

    if (index != -1) {
        ((void (*)(int))*(int *)(*(char **)(data_ov009_020562dc + index * 8) + 4))(arg0);
    }
}
