struct sc1c7 { signed char _pad[0x1c7]; signed char status; };
int func_ov240_020ce594(int param_1)
{
    int e = *(int *)(param_1 + 0x214);
    int s = *(int *)e;
    int neg = -1;
    if (((struct sc1c7 *)s)->status == neg) {
        ((struct sc1c7 *)s)->status = 0xa;
        return 1;
    }
    return 0;
}
