extern void func_0203c640();

struct sub { unsigned char pad[0xad]; unsigned char flag; };
struct outer { int x; struct sub **p; };

void func_ov244_020ce7b8(struct outer *a) {
    if ((*a->p)->flag == 0) {
        func_0203c640(a);
    }
}
