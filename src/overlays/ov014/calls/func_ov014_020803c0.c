typedef struct {
    char pad[0x134];
    signed char state;
} Ov014Object;

extern int func_ov002_020573cc(void);
extern int func_ov002_020766e0(Ov014Object *self, unsigned char *record, int size);

int func_ov014_020803c0(Ov014Object *self, unsigned char *value)
{
    unsigned char record[6];

    if (self->state != 0) {
        return 0;
    }
    if (func_ov002_020573cc() != 0) {
        return 0;
    }

    record[0] = 1;
    record[4] = *value;
    func_ov002_020766e0(self, record, 6);
    self->state = 1;
    return 0;
}
