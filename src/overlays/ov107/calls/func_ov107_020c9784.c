typedef struct Ov107_9784_Entry {
    char pad[0xc];
    void (*callback)(struct Ov107_9784_Entry *entry, int b);
    char pad2[0x40 - 0x10];
    int flags;
} Ov107_9784_Entry;

typedef struct Ov107_9784_Self {
    char pad[0x3c];
    void *field_3c;
    int flags;              /* 0x40 */
    char pad2[0x44 - 0x44]; /* list head starts right at 0x44 */
    char list[0x78 - 0x44];
    int accum;               /* 0x78 */
    char pad3[0xa4 - 0x7c];
    int field_a4;             /* 0xa4 */
} Ov107_9784_Self;

extern int func_01fffd70(void *listHead);
extern int func_01fffd8c(void *listHead);
extern int func_ov107_020c2034(void *entry);
extern void func_ov107_020c2c94(void *self, int b);
extern void func_0203c4a8(void *ptr, int b);

void func_ov107_020c9784(Ov107_9784_Self *self, int b)
{
    int allBit2 = 1;
    void *node;

    self->accum = 0;
    self->field_a4 += b;

    node = (void *)func_01fffd70(self->list);
    while (node != 0) {
        Ov107_9784_Entry *entry = *(Ov107_9784_Entry **)node;
        int flags = entry->flags;

        if (!((flags << 0x1d) >> 0x1f)) {
            if ((flags << 0x1e) >> 0x1f) {
                if (entry->callback != 0) {
                    entry->callback(entry, b);
                }
            }
            allBit2 = 0;
        } else {
            self->accum += func_ov107_020c2034(entry);
        }
        node = (void *)func_01fffd8c(self->list);
    }

    self->flags = (self->flags & ~4) | ((unsigned int)(allBit2 << 31) >> 29);
    func_ov107_020c2c94(self, b);
    func_0203c4a8(self->field_3c, b);
}
