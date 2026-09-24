/* Saves the 24 word slots of data_0204c6b4 and the 15 halfword slots of data_0204c714 into the
 * save buffer (data_0204c4f0[2], words first, halfwords at +0x60); the counterpart of
 * func_02035cac. */
#pragma thumb on
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

extern char *data_0204c4f0[];
extern char data_0204c6b4[];
extern char data_0204c714[];

void func_02035c60(void)
{
    char *dst;
    char *src;
    int i;
    char *p;

    p = data_0204c4f0[2];

    src = data_0204c6b4;
    for (i = 0, dst = p; i < 24; i++) {
        MI_CpuCopy8(src, dst, 4);
        dst += 4;
        src += 4;
    }
    src = data_0204c714;
    i = 0;
    p += 0x60;
    for (; i < 15; i++) {
        MI_CpuCopy8(src, p, 2);
        p += 2;
        src += 2;
    }
}
