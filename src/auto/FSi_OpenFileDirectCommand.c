int FSi_OpenFileDirectCommand(int *p)
{
    p[9] = p[12];
    p[11] = p[12];
    p[10] = p[13];
    p[8] = p[14];
    return 0;
}
