/* Tail-call ActionScript_RequestSkip with the global at data_ov106_020b8b60. */
extern int ActionScript_RequestSkip(int arg);
extern int data_ov106_020b8b60;
int Ov106_ArmObject(void) {
    return ActionScript_RequestSkip(*(int *)&data_ov106_020b8b60);
}
