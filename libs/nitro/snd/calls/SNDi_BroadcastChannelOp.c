extern void func_02019fbc(int a, int b);

void SNDi_BroadcastChannelOp(int arg0)
{
    int i;
    for (i = 2; i < 0x20; i++) {
        func_02019fbc(i, arg0);
    }
}
