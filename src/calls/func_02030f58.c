typedef unsigned int u32;

extern void func_02023728(u32 a, u32 b);
extern void func_0203112c(void);
extern void WM_EndKeySharing_0x02023ad0(void *p);

extern u32 **data_0204c230;
extern u32 *data_0204c024;

void func_02030f58(void)
{
    u32 *r6;
    int j;
    char *r7;
    int r4;
    int r5;
    u32 *p;
    int k;

    r6 = (u32 *)data_0204c230;
    if (r6 == 0) goto end;
    j = 0;
    if ((int)r6[2] > 0) {
        r7 = (char *)0;
        do {
            r4 = 0;
            r5 = 0;
            do {
                p = (u32 *)(r7 + r6[1] + r5);
                func_02023728(p[1], (u32)data_0204c024);
                r4++;
                r5 += 0xc;
            } while (r4 < 2);
            r7 += 0x20;
            j++;
        } while (j < (int)r6[2]);
    }
    func_02023728(r6[1], (u32)data_0204c024);
    func_0203112c();
    r5 = 0x758;
    r4 = 0;
    do {
        WM_EndKeySharing_0x02023ad0((void *)*(u32 *)((char *)r6 + r5));
        r4++;
        r6 = (u32 *)((char *)r6 + 4);
    } while (r4 < 2);
end:
    data_0204c230 = 0;
}
