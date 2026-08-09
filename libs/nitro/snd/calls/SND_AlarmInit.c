/* SND_AlarmInit: zeroes the 8 alarm slots (stride 0xc): handler, arg, and id byte. */

extern unsigned char data_02046220;

void SND_AlarmInit(void) {
    int i;
    char *p = (char *)&data_02046220;

    for (i = 0; i < 8; i++) {
        *(int *)p = 0;
        *(int *)(p + 4) = 0;
        *(unsigned char *)(p + 8) = 0;
        p += 0xc;
    }
}
