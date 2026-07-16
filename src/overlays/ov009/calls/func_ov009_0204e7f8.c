extern int data_ov009_020563ec[];
extern char data_ov009_020562d4[];

void func_ov009_0204e7f8(int arg0)
{
    int index = data_ov009_020563ec[1];

    if (index != -1) {
        ((void (*)(int))*(int *)(*(char **)(data_ov009_020562d4 + index * 8) + 4))(arg0);
    }
}
