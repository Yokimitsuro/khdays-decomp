extern int func_0200cd40(int arg);

int PXIi_RouteByChannelId(int arg0)
{
    int v;
    switch (arg0) {
    case 1: v = 1; break;
    case 3: v = 2; break;
    case 2: v = 3; break;
    default: v = 0; break;
    }
    if (v == 0) return 0xffff;
    return func_0200cd40(v);
}
