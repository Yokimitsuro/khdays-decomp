void NNS_FndInitList(void *list, unsigned short offset)
{
    ((int *)list)[0] = 0;
    ((int *)list)[1] = 0;
    ((unsigned short *)list)[4] = 0;
    ((unsigned short *)list)[5] = offset;
}
