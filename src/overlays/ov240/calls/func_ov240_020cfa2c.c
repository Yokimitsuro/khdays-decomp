extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_ov240_020ce8d4(int obj, int arg);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov240_020cfa6c(void);

void func_ov240_020cfa2c(char *obj) {
    char *p = *(char **)(obj + 4);
    func_ov107_020c9264(*(int *)p, 2, 1);
    func_ov240_020ce8d4(*(int *)p, 0);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov240_020cfa6c);
}
