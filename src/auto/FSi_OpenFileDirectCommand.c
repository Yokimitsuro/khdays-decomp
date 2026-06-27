int FSi_OpenFileDirectCommand(int *param)
{
    param[9] = param[12];
    param[11] = param[12];
    param[10] = param[13];
    param[8] = param[14];
    return 0;
}
