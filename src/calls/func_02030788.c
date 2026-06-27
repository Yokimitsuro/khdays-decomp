extern int func_02030670(void *p);
extern unsigned char *data_0204c228;

unsigned int func_02030788(void)
{
    unsigned char *p = data_0204c228;
    if (p != 0 && func_02030670(&data_0204c228) != 0) {
        return *(unsigned short *)(p + 0x22);
    }
    return 0;
}
