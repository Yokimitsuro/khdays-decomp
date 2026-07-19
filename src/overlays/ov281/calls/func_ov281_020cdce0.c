extern int func_ov107_020c9f48(int a, void *out);
extern void func_0202f384(int a, int b, void *c);
extern void func_01ffa724(int a, int b, int c);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int *self, int idx, void *cb);
extern void func_ov281_020cdd94(void);

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov281_020cdce0(int *self) {
    int v[3];
    int *s = (int *)self[1];
    int r = func_ov107_020c9f48(*(int *)(*s + 0x3c0), v);
    func_0202f384((int)s + 0x20, *s + 0xa0, v);
    func_01ffa724(r, (int)s + 0x20, (int)s + 0x20);
    if (*(unsigned char *)(s[1] + 0xad) != 0) return;
    func_ov107_020c9264(*s, 9, 1);
    ((struct hw60 *)(*s + 0x60))->hi &= ~0x40;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), (void *)&func_ov281_020cdd94);
}
