/* WH_SetJudgeAcceptFunc (wh.c): the callback that decides whether a child may connect. */
extern int data_ov105_020c04c0;
void Ov105_WH_SetJudgeAcceptFunc(int param_1) {
    *(int *)((char *)&data_ov105_020c04c0 + 0x38) = param_1;
}
