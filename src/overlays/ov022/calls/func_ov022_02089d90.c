extern int func_02030788(void);
extern void func_ov022_02088a5c(int kind, int id, int a2, int a3);
extern void func_ov022_02088b50(int kind, int a2, int id);
extern void func_ov022_02088cac(int kind);

struct Ent02089d90 {
    unsigned short id;
    unsigned char a2;
    unsigned char a3;
    unsigned char sel : 3;
    unsigned char kind : 3;
};

void func_ov022_02089d90(int arg0) {
    struct Ent02089d90 *e = (struct Ent02089d90 *)arg0;
    switch (e->sel) {
    case 0:
        if (func_02030788() == 0) return;
        func_ov022_02088a5c(e->kind, e->id, e->a2, e->a3);
        return;
    case 1:
        func_ov022_02088b50(e->kind, e->a2, e->id);
        return;
    case 2:
        if (func_02030788() == 0) return;
        func_ov022_02088cac(e->kind);
        return;
    }
}
