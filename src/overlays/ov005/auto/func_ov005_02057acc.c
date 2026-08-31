typedef unsigned short u16;
u16 func_ov005_02057acc(int factorQ12) {
    int scaledQ12=(int)(((long long)factorQ12*0x3e8000+0x800)>>12);
    int tenthsPercent=scaledQ12>>12;
    int adjustment=0;
    if(tenthsPercent%10>=5)adjustment=10;
    tenthsPercent+=adjustment;
    tenthsPercent/=10;
    return (u16)tenthsPercent;
}
