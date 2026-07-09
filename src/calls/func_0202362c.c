extern int data_0204c028;

int func_0202362c(int arg0) {
    int head = *(int *)&data_0204c028;
    *(int *)&data_0204c028 = (arg0 == 0) ? *(int *)((char *)&data_0204c028 + 4) : arg0;
    return head;
}
