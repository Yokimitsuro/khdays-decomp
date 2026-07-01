void OS_InitMutex(int *mutex)
{
    mutex[1] = 0;
    mutex[0] = 0;
    mutex[2] = 0;
    mutex[3] = 0;
}
