typedef unsigned char u8;

struct Ov190Vec3 {
    int x;
    int y;
    int z;
};

struct Ov190Transform {
    int words[11];
};

struct Ov190Command {
    u8 pad00[2];
    u8 type02;
    u8 action03;
    u8 target04;
    u8 packedPosition05[9];
};

struct Ov190NodeSlot {
    int node;
    int handle;
};

struct Ov190Actor {
    char pad000[0x3c];
    int resource03c;
    char pad040[0x60];
    struct Ov190Transform transform0a0;
    char pad0cc[0x2f8];
    int specialHandle3c4;
    struct Ov190NodeSlot nodes3c8[4];
};

extern void func_0203c960(struct Ov190Transform *transform);
extern void func_0203ca30(struct Ov190Transform *transform,
                          const struct Ov190Vec3 *position);
extern int func_ov107_020c0794(int resource, int node, int kind, int flags,
                               struct Ov190Transform *transform);
extern int func_ov107_020c09a0(int resource, int node, int kind,
                               struct Ov190Transform *transform, int flags,
                               int enabled);
extern int func_ov107_020cb040(struct Ov190Actor *self, int resourceId,
                               int kind, int enabled,
                               struct Ov190Transform *transform);
extern void func_0203c650(int resource, int handle);
extern void func_ov107_020cb100(int handle);
extern void func_ov107_020c7500(struct Ov190Actor *self,
                                struct Ov190Command *command, int arg2);

void func_ov190_020d3cb4(struct Ov190Actor *self,
                         struct Ov190Command *command, int arg2)
{
    struct Ov190Transform transform;
    struct Ov190Vec3 position;
    union {
        int words[3];
        u8 bytes[12];
    } packed;

    if (command->type02 == 5) {
        func_0203c960(&transform);

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

        func_0203ca30(&transform, &position);

        switch (command->action03) {
        case 0:
            self->nodes3c8[command->action03].handle =
                func_ov107_020c0794(self->resource03c,
                                    self->nodes3c8[command->action03].node,
                                    5, 0, &transform);
            break;
        case 1:
        case 2:
            transform = self->transform0a0;
            self->nodes3c8[command->action03].handle =
                func_ov107_020c0794(self->resource03c,
                                    self->nodes3c8[command->action03].node,
                                    5, 0, &transform);
            break;
        case 3:
            self->nodes3c8[command->action03].handle =
                func_ov107_020c09a0(self->resource03c,
                                    self->nodes3c8[command->action03].node,
                                    5, &self->transform0a0, 0, 1);
            break;
        case 4:
            break;
        case 5:
            self->specialHandle3c4 =
                func_ov107_020cb040(self, 0x12f, 8, 1,
                                    &self->transform0a0);
            break;
        case 6:
            if (self->nodes3c8[3].handle != 0) {
                func_0203c650(self->resource03c,
                              self->nodes3c8[3].handle);
                self->nodes3c8[3].handle = 0;
            }
            if (self->specialHandle3c4 != 0) {
                func_ov107_020cb100(self->specialHandle3c4);
                self->specialHandle3c4 = 0;
            }
            break;
        }
    }

    func_ov107_020c7500(self, command, arg2);
}






