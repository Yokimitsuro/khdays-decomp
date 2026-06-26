int OS_IsThreadTerminated(int *p)
{
    return p[0x19] == 2;
}
