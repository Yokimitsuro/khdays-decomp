typedef unsigned int u32;
typedef unsigned short u16;

extern void *func_0203d15c(u32 size);
extern void *func_0203b898(void *arg0);
extern void func_0203c7ac(int *ptr, int arg);
extern int func_0203bdfc(void *a0, void *a1);
extern void func_ov107_020c9c90(void);

typedef struct Ov107_9e50_Inner {
    char pad[0x6c];
    void *field_6c;
    char pad2[0x84 - 0x70];
    void *field_84;
} Ov107_9e50_Inner;

typedef struct Ov107_9e50 {
    u16 field_00;
    char pad[0x3a];
    Ov107_9e50_Inner *field_3c;
} Ov107_9e50;

void *func_ov107_020c9e50(int a, const void *b)
{
    Ov107_9e50 *self = (Ov107_9e50 *)func_0203d15c(0x40);
    self->field_3c = (Ov107_9e50_Inner *)func_0203b898((void *)a);
    self->field_3c->field_6c = (void *)func_ov107_020c9c90;
    self->field_3c->field_84 = self;
    func_0203c7ac((int *)self->field_3c, 0);
    self->field_00 = (u16)func_0203bdfc(self->field_3c, (void *)b);
    return self;
}
