#pragma thumb on

/* Clear transient AI flags, queue the adjusted vec74 position when field_50 is
 * one, send scaled notifications to eligible player slots, and run cleanup hooks.
 *
 * Coordinates are held in a one-value wrapper type (Fx32), a tentative
 * reconstruction of the original's coordinate type (same as func_ov107_020c9474,
 * func_ov107_020c4bf0 and func_ov107_020c5af8). Copying a wrapped value is a
 * struct copy, which mwcc keeps; that is the ROM's unread stack copy of the
 * position at sp+0, sp+4 and sp+8.
 *
 * Frame layout (0x2c): mwcc places locals of 8 bytes or less below the larger
 * ones, and within each group the first declared gets the highest offset. So the
 * 4-byte notification (sp+0xc) is declared before the three 4-byte coordinate
 * copies, and those are declared z, y, x to put x at sp+0.
 *
 * data_ov107_020cb628 is in ov107's .rodata range, so its declaration is const.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;

typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
typedef struct { u8 hi, mid, lo; } PackedFx24;

typedef struct {
    u16 id;
    u8 type;
    u8 field_03;
} MessageHeader;

typedef struct {
    MessageHeader header;
    u8 field_04;
    PackedFx24 position[3];
} MessagePacket;

typedef struct {
    u16 id;
    u8 field_02;
    u8 field_03;
} Notification;

/* The format keeps the sign bit and the low 23 bits, most significant byte first. */
static inline void EncodeCoordinate(PackedFx24 *packed, int coordinate)
{
    packed->hi = (u8)(((u32)coordinate >> 16 & 0x7f) |
                     ((u32)coordinate >> 24 & 0x80));
    packed->mid = (u8)((u32)coordinate >> 8);
    packed->lo = (u8)coordinate;
}


/* Partial layouts: only accesses established by this function and its siblings. */
typedef struct AiState AiState;
struct Flags16 { u16 lo : 8, hi : 8; };
typedef struct {
    u8 pad000[0x78];
    int field_78;
} AiContext;
typedef struct {
    u8 pad000[2];
    s16 field_02;
    u8 pad004[0x64];
    s16 field_68;
} HitTable;
typedef struct LinkedObject LinkedObject;
struct LinkedObject {
    u8 pad000[0x18c];
    void *field_18c;
    u8 pad190[0x24];
    u8 field_1b4;
    u8 pad1b5[0x17];
    int (*field_1cc)(void *);
    void (*field_1d0)(LinkedObject *, int);
};
struct AiState {
    u8 pad000[2];
    u16 field_02;
    AiContext *field_04;
    u8 pad008[0x1c];
    void (*field_24)(AiState *, void *, int);
    u8 pad028[0x28];
    int field_50;
    u8 pad054[0xc];
    struct Flags16 flags60;
    u8 pad062[0x12];
    FxVec vec74;
    int field_80;
    u8 pad084[0xf5];
    u8 field_179;
    u8 pad17a[0x25];
    u8 field_19f;
    HitTable *field_1a0;
    u8 pad1a4[0x21];
    u8 field_1c5;
    u8 pad1c6[0x22];
    void (*field_1e8)(AiState *);
    u8 pad1ec[0x70];
    LinkedObject *field_25c;
    u8 pad260[0x74];
    int field_2d4;
    u8 pad2d8[0x1c];
    int field_2f4;
    int field_2f8;
    u8 pad2fc[0x58];
    u32 field_354;
};

typedef struct {
    u8 pad000[0xa8];
    int field_a8;
} ManagerSettings;

typedef struct {
    u8 pad000[0x18c];
    void *field_18c;
} PlayerSlot;

typedef struct {
    ManagerSettings *field_00;
    u8 pad004[0x28];
    PlayerSlot *slots[4];
    u8 pad03c[0x50];
    int field_8c;
} ActorManager;

extern int func_02005418(int a, int b);
extern ActorManager *OS_IsThreadAvailable_0x020c9848(void);
extern int func_ov002_02072754(int value);
extern u16 func_02031384(int kind, const void *pCmd, u16 size);
extern void func_ov022_02088984(int player, int value);
extern void func_ov022_020889cc(int player, int value);
extern const Notification data_ov107_020cb628[];

void func_ov107_020c7da4(AiState *self)
{
    AiContext *context;
    int notificationAmount;
    int i;
    FxVec position;
    Notification notification;

    context = self->field_04;
    self->field_1c5 &= ~0xf;

    if (self->field_25c != 0 &&
        self->field_25c->field_1d0 != 0 &&
        self->field_1a0 != 0) {
        int multiplier = func_02005418(self->field_1a0->field_68 << 4, self->field_2f8);
        int amount = func_02005418(multiplier,
            OS_IsThreadAvailable_0x020c9848()->field_8c) + 0x800;
        self->field_25c->field_1d0(self->field_25c, amount >> 12);
    }

    notificationAmount = 0;
    func_ov002_02072754(context->field_78);
    position = self->vec74;
    position.y.value += self->field_80;

    if (self->field_50 == 1) {
        MessagePacket message = { 0 };
        /* The header goes through a pointer so mwcc addresses it off its own
         * base register, as the ROM does (same as func_ov107_020c5af8). */
        MessageHeader *header = (MessageHeader *)&message;
        Fx32 z, y, x;
        header->id = self->field_02;
        header->type = 9;
        x = position.x;
        EncodeCoordinate(&message.position[0], x.value);
        y = position.y;
        EncodeCoordinate(&message.position[1], y.value);
        z = position.z;
        EncodeCoordinate(&message.position[2], z.value);
        func_02031384(4, &message, 0xe);
    }

    if (self->field_1a0 != 0) {
        if (self->field_2f4 > 0) {
            notificationAmount = (func_02005418(self->field_2f4,
                self->field_1a0->field_02 << 4) + 0xfff) >> 12;
        } else if (OS_IsThreadAvailable_0x020c9848()->field_00->field_a8 > 0) {
            notificationAmount = (func_02005418(
                OS_IsThreadAvailable_0x020c9848()->field_00->field_a8,
                self->field_1a0->field_02 << 4) + 0xfff) >> 12;
        } else {
            notificationAmount = ((self->field_1a0->field_02 << 4) + 0xfff) >> 12;
        }
    }

    for (i = 0; i < 4; i++) {
        ActorManager *manager = OS_IsThreadAvailable_0x020c9848();
        PlayerSlot *slot = manager ? manager->slots[i] : 0;
        if (slot != 0 && slot->field_18c != 0) {
            func_ov022_02088984(i, notificationAmount);
        }
    }

    if (self->field_25c != 0) {
        func_ov022_020889cc(self->field_25c->field_1b4,
                            self->field_19f);
    } else {
        func_ov022_020889cc(0, self->field_19f);
    }

    if (self->field_179 != 1) {
        self->flags60.hi &= ~1;
    }

    if (self->field_354 != 0) {
        LinkedObject *resource;
        notification = data_ov107_020cb628[2];
        resource = self->field_25c;
        if (resource != 0 && resource->field_1cc != 0 &&
            resource->field_1cc(resource->field_18c) != 0) {
            notification.field_03 -= 1;
        }
        if (self->field_24 != 0) {
            self->field_24(self, &notification, 4);
        }
    }

    if (self->field_1e8 != 0) {
        self->field_1e8(self);
    }
    self->field_1e8 = 0;
    self->field_2d4 = 0;
}
