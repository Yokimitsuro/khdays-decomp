/* Attach/refresh `obj` on entity[index]'s container. When p3 and func_0202b0b8
 * both yield a transform, optionally compose it with p4 (VEC_Add), apply
 * via func_0202b330, cache the func_0202b150 result at obj+0x8c and set flag
 * 0x20; otherwise apply p4 directly. Then set state bits 0xa on obj+8 and
 * (re)link it into the 0x64 or 0x84 list by that bit. */
extern int data_0204c208;
extern int func_0202b0b8(void *cont, int p3, void *out);
extern void VEC_Add(void *a, void *b, void *c);
extern void func_0202b330(void *cont, void *field, void *vec);
extern int func_0202b150(void *cont, int p3);
extern void func_0202b480(int index, void *obj);
extern void func_0202b540(int index, void *obj);

void func_0202ba9c(void *obj, int index, int p3, void *p4) {
    void *cont = (void *)(data_0204c208 + 4 + index * 8);
    unsigned int buf[3];
    if (p3 != 0 && func_0202b0b8(cont, p3, buf) != 0) {
        if (p4 != 0) {
            VEC_Add(buf, p4, buf);
        }
        func_0202b330(cont, (char *)obj + 0xc, buf);
        {
            int r = func_0202b150(cont, p3);
            if ((*(int *)((char *)obj + 0xc) & 0x20) == 0) {
                *(short *)((char *)obj + 0x8c) = (short)r;
                *(unsigned short *)((char *)obj + 0x10) |= 0x20;
            }
        }
    } else {
        func_0202b330(cont, (char *)obj + 0xc, p4);
    }
    {
        unsigned char v = *(unsigned char *)((char *)obj + 8);
        v |= 0xa;
        *(unsigned char *)((char *)obj + 8) = v;
        if (v & 0x20) {
            func_0202b480(index, obj);
        } else {
            func_0202b540(index, obj);
        }
    }
}
