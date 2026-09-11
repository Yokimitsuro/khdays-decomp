typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 f0;
    u8 f1;
    signed char f2;
    signed char f3;
} Entry;

extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);

int func_ov107_020c1744(int self, int index)
{
    int t4 = *(int *)(self + 4);
    if (t4 == 0) return 0;

    u8 key = *(u8 *)(self + index * 12 + 0x50);
    int t5 = *(int *)(t4 + 4);

    if (t5 != 0) {
        u8 *arr9c = *(u8 **)(t5 + 0x9c);
        u8 val = arr9c[key];
        if (val != 0) {
            u8 *arra0 = *(u8 **)(t5 + 0xa0);
            u8 cur = arra0[key];
            if (cur >= val) return 0;
        }
    }

    {
        void *raw = func_01fffd70((void *)(t4 + 0x80));
        void *node = !raw ? 0 : *(void **)raw;

        while (node != 0) {
            int n = (int)node;
            unsigned int flags60 = (unsigned int)(*(u16 *)(n + 0x60) << 24) >> 24;

            if (flags60 & 1) goto loopend;
            if (!(flags60 & 0x80)) goto loopend;
            if (!(*(u16 *)(n + 0x1ac) & 0x80)) goto loopend;
            if (*(int *)(n + 0x2e8) > 0) goto loopend;
            if (*(int *)(n + 0x2d4) != 0) goto loopend;

            {
                Entry *ip = *(Entry **)(t5 + 0x94);

                if (*(u8 *)(n + 0x19c) != ip[key].f1) goto loopend;

                if (ip[key].f2 != 0 && *(u8 *)(n + 0x19d) != ip[key].f2) goto loopend;

                if ((*(Entry **)(t5 + 0x94))[key].f3 != 0 &&
                    *(u8 *)(n + 0x19e) != (*(Entry **)(t5 + 0x94))[key].f3) goto loopend;
            }

            {
                u8 *arra0 = *(u8 **)(t5 + 0xa0);
                arra0[key] = arra0[key] + 1;
            }
            return n;

        loopend:
            raw = func_01fffd8c((void *)(t4 + 0x80));
            node = !raw ? 0 : *(void **)raw;
        }
    }

    return 0;
}
