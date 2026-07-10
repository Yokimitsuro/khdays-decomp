extern void func_02035830(int kind, unsigned short *pair);
extern unsigned short *func_0203583c(int kind, unsigned int id);
extern int func_02030788(void);
extern void func_ov002_0205de68(int a, int b);

void func_ov022_020aa788(int obj, unsigned int id, unsigned short arg2) {
    unsigned short pair[2];
    unsigned short *e;
    pair[0] = (unsigned short)id;
    pair[1] = arg2;
    func_02035830(*(unsigned char *)(obj + 9), pair);
    e = func_0203583c(*(unsigned char *)(obj + 9), id);
    if (*(unsigned char *)(obj + 8) != func_02030788()) return;
    if ((*(unsigned long long *)obj & 0x10000LL) != 0) return;
    if (e != 0) func_ov002_0205de68(e[0], e[1]);
    else func_ov002_0205de68((unsigned short)id, 0);
}
