typedef unsigned char u8;
typedef unsigned short u16;

struct Ov234Vec3 {
    int x;
    int y;
    int z;
};

struct Ov234Transform {
    int words[11];
};

struct Ov234Command {
    u8 pad00[2];
    u8 type02;
    u8 action03;
    u8 target04;
    u8 packedPosition05[9];
};

struct Ov234NodeSlot {
    int node;
    int handle;
};

struct Ov234Actor {
    char pad000[0x3c];
    int resource03c;
    char pad040[0x378];
    int value3b8;
    struct Ov234NodeSlot nodes3bc[7];
};

extern u8 data_0204c240;

extern int func_01fffe14(void);
extern int func_020235d0(int, int);
extern void func_020235e8(int, int, int);
extern void func_0203c960(struct Ov234Transform *);
extern void func_0203ca30(struct Ov234Transform *, const struct Ov234Vec3 *);
extern void func_ov002_0206bbb8(int, int, int);
extern int func_ov107_020c0794(int, int, int, int, struct Ov234Transform *);
extern void func_ov107_020c7500(struct Ov234Actor *, struct Ov234Command *, int);

void func_ov234_020cc274(struct Ov234Actor *self, struct Ov234Command *command,
                         int arg2)
{
    struct Ov234Transform transform;
    struct Ov234Vec3 position;
    union {
        int words[3];
        u8 bytes[12];
    } packed;

    if (command->type02 == 5) {
        int oldValue;
        int delta;

        packed.bytes[3] = command->packedPosition05[0];
        packed.bytes[2] = command->packedPosition05[1];
        packed.bytes[1] = command->packedPosition05[2];
        position.x = packed.words[0] >> 8;
        packed.bytes[7] = command->packedPosition05[3];
        packed.bytes[6] = command->packedPosition05[4];
        packed.bytes[5] = command->packedPosition05[5];
        position.y = packed.words[1] >> 8;
        packed.bytes[11] = command->packedPosition05[6];
        packed.bytes[10] = command->packedPosition05[7];
        packed.bytes[9] = command->packedPosition05[8];
        position.z = packed.words[2] >> 8;

        func_0203c960(&transform);
        func_0203ca30(&transform, &position);

        switch (command->action03) {
        case 0:
            self->nodes3bc[command->action03].handle =
                func_ov107_020c0794(self->resource03c,
                                    self->nodes3bc[command->action03].node,
                                    5, 0, &transform);
            break;
        case 1:
            break;
        case 2:
            oldValue = self->value3b8;
            if (oldValue < 999) {
                self->value3b8 = oldValue + 1;
                if (self->value3b8 >= 999) {
                    self->value3b8 = 999;
                }
                delta = self->value3b8 - oldValue;
                func_ov002_0206bbb8(func_01fffe14(), 3, delta);
                if (data_0204c240 & 4) {
                    func_ov002_0206bbb8(command->target04, 7, delta);
                }
            }
            break;
        case 3:
            if (!(data_0204c240 & 4)) {
                int queryValue = func_020235d0(0x1400, 10);
                int actorValue = *(volatile int *)&self->value3b8;
                if (queryValue < actorValue) {
                    func_020235e8(0x1400, 10, (u16)actorValue);
                }
            }
            break;
        case 4:
            if (!(data_0204c240 & 4)) {
                int queryValue = func_020235d0(0x1400, 10);
                int actorValue = *(volatile int *)&self->value3b8;
                if (queryValue < actorValue) {
                    func_020235e8(0x1400, 10, (u16)actorValue);
                }
            }
            self->value3b8 = 0;
            func_020235e8(0x208f, 10, 0);
            func_ov002_0206bbb8(func_01fffe14(), 3, 0);
            if (data_0204c240 & 4) {
                func_ov002_0206bbb8(command->target04, 7, 0);
            }
            break;
        case 5:
            self->value3b8 = 0;
            func_020235e8(0x208f, 10, 0);
            break;
        case 6:
            func_020235e8(0x20dc, 1, 1);
            break;
        }
    }

    func_ov107_020c7500(self, command, arg2);
}
