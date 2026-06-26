void *DLAddFront(void *r0, int *r1)
{
    r1[1] = (int)r0;
    r1[0] = 0;
    if (r0 != 0)
        *(int *)r0 = (int)r1;
    return r1;
}
