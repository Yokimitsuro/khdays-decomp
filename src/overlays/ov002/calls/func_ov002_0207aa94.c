/* Announce the object's state. In a session that is a 6-byte message 3 carrying
 * the state byte from +0x3f; solo, there is nobody to tell, so the state is just
 * written straight to +0x2c. */
extern int func_02030670(void);
extern void func_ov002_020766e0(void *self, void *message, int size);

typedef struct {
    char pad0000[0x2c];
    unsigned char bLocalState;  /* +0x2c */
    char pad002d[0x12];
    unsigned char bState;       /* +0x3f */
} Ov002Announcer;

void func_ov002_0207aa94(Ov002Announcer *self) {
    unsigned char message[8];

    if (func_02030670() != 0) {
        self->bLocalState = 4;
        return;
    }

    message[0] = 3;
    message[4] = self->bState;
    func_ov002_020766e0(self, message, 6);
}
