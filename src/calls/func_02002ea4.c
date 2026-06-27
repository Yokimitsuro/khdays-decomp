extern void OSi_ExceptionHandler(void);
extern char data_020445b4[];

void func_02002ea4(void)
{
    unsigned int v = *(volatile unsigned int *)0x027FFD9Cu;
    if (v >= 0x02600000u && v < 0x02800000u) {
        *(unsigned int *)data_020445b4 = v;
    } else {
        *(unsigned int *)data_020445b4 = 0;
    }
    if (*(unsigned int *)data_020445b4 == 0) {
        *(volatile void **)0x027FFD9Cu = (void *)OSi_ExceptionHandler;
        {
            volatile char *base = (volatile char *)0x027E3000u;
            *(volatile void **)(base + 0xFDC) = (void *)OSi_ExceptionHandler;
        }
    }
    *(unsigned int *)(data_020445b4 + 8) = 0;
}
