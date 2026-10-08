/* WH_SetGgid (wh.c): the game group id the parent announces (sParentParam.ggid). */
extern int data_ov105_020c0580;
void Ov105_WH_SetGgid(int param_1) {
    *(int *)((char *)&data_ov105_020c0580 + 8) = param_1;
}
