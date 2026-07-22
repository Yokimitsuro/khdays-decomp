extern int data_ov002_0207fa00;

void func_ov002_0206d880(int arg0) {
    char *session = (char *)(*(int *)&data_ov002_0207fa00 + 0x8c94);
    char idle;

    if (arg0 == 0) {
        idle = 1;
    } else {
        idle = 0;
    }
    session[0x77] = idle;
}
