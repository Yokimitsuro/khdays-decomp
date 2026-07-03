void func_ov009_02052abc(unsigned int value, unsigned short *hours, char *minutes, char *seconds)
{
    if (seconds != 0)
        *seconds = (char)(value % 60);
    if (minutes != 0)
        *minutes = (char)((value / 60) % 60);
    if (hours != 0)
        *hours = (unsigned short)(value / 3600);
    if (*hours > 999) {
        *hours = 999;
        *minutes = ';';
        *seconds = ';';
    }
}
