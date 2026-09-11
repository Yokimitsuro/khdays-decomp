typedef struct { int w[3]; } Blk12;

extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern int func_02023eb4(unsigned int mul);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov283_020cd27c(void);
extern Blk12 data_02041dc8;

void func_ov283_020cd200(char *obj) {
    char *p = *(char **)(obj + 4);
    func_ov107_020c9264(*(int *)p, 0, 1);
    *(Blk12 *)(p + 0x10) = data_02041dc8;
    *(int *)(p + 0x5c) = 0;
    int min = *(int *)(*(char **)p + 0x224);
    int range = *(int *)(*(char **)p + 0x228) - min;
    if (range < 0) range = -range;
    *(int *)(p + 0x48) = min + func_02023eb4(range + 1);
    *(int *)(p + 0x78) = 0;
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov283_020cd27c);
}
