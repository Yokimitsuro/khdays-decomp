extern int data_027e0074;

void func_02016264(int *arg0) {
    if (*(int *)&data_027e0074 == 0) {
        *arg0 = 0;
        *(int *)&data_027e0074 = (int)arg0;
    }
}
