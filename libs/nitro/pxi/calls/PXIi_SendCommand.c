extern int func_020093e8(int a, int b, int c);

void PXIi_SendCommand(int arg0)
{
    while (func_020093e8(8, arg0, 0) != 0);
}
