int NNS_FndGetPrevListObject(unsigned short *r0, char *r1)
{
    if (r1 == 0)
        return ((int *)r0)[1];
    return *(int *)(r1 + r0[5]);
}
