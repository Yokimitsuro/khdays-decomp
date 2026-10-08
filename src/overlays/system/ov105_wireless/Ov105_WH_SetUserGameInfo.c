/* WH_SetUserGameInfo (wh.c): the user game info the parent's beacon carries and its
 * length (sParentParam.userGameInfo / userGameInfoLength). */
extern int data_ov105_020c0580;
void Ov105_WH_SetUserGameInfo(int param_1, int param_2) {
    *(int *)&data_ov105_020c0580 = param_1;
    *(unsigned short *)((char *)&data_ov105_020c0580 + 4) = (unsigned short)param_2;
}
