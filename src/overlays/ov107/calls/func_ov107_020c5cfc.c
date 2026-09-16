typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { int x, y, z; } VecFx32;
/* Tentative reconstruction of the coordinate type; wrapper copies retain the
 * unread coordinate stores present in the ROM, as in func_ov107_020c5af8. */
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;

struct Obj;
struct HitPacket;
struct LookupEntry { u8 pad000[0xc]; int field_0c; };
struct HitSource {
    u8 pad000[0x1c8];
    struct LookupEntry *(*field_1c8)(int);
};

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x24];
    int field_24;                 /* 0x024 */
    unsigned char pad028[0x38];
    unsigned short flags60;       /* 0x060 */
    unsigned char pad062[0x1e];
    int field_80;                 /* 0x080 */
};

/* Additional, partial view of the same header; the union retains the canonical view. */
struct ObjectHeader {
    u16 field_00;
    u16 field_02;
    u8 pad004[0x4c];
    int field_50;
    u8 pad054[0x20];
    FxVec field_74;
};
struct Table { u8 pad000[0x50]; u8 field_50; u8 pad051[0x13]; short field_64; };
struct Threshold { int field_00, field_04, field_08; };

/* Partial combat object, extending the canonical header with observed fields. */
struct Obj {
    union { struct AiState ai; struct ObjectHeader extra; } header;
    u8 pad084[0xf5];
    u8 field_179;
    u8 pad17a[0x26];
    struct Table *field_1a0;
    u8 pad1a4[8];
    u16 field_1ac;
    u16 field_1ae;
    u16 field_1b0;
    u16 field_1b2;
    int field_1b4[4];
    u8 field_1c4;
    u8 field_1c5;
    u8 pad1c6[2];
    struct LookupEntry *(*field_1c8)(int);
    int field_1cc;
    int (*field_1d0)(struct Obj *, struct HitSource *, struct HitPacket *);
    void (*field_1d4)(struct Obj *, struct Obj *);
    u8 pad1d8[0x40];
    short field_218;
    short field_21a;
    u8 pad21c[0x38];
    int field_254;
    int field_258;
    struct HitSource *field_25c;
    u8 pad260[0x7c];
    u16 field_2dc;
    u16 field_2de;
    int field_2e0;
    int field_2e4;
    int field_2e8;
    int field_2ec;
    int field_2f0;
    int field_2f4;
    int field_2f8;
    u8 pad2fc[0x18];
    struct Threshold field_314[5];
};
struct HitPacket {
    u32 flagsLo : 16;
    u32 flagsHi : 16;
    VecFx32 normal;
    int field_10 : 16;
    int field_12 : 16;
    int field_14 : 16;
    int field_16 : 16;
    void *field_18;
    signed char field_1c;
    u8 pad01d[3];
    int field_20;
    u32 flags24Lo : 16;
    u32 flags24Hi : 16;
    int field_28;
};
struct Manager {
    u8 pad000[0x2c];
    struct Obj *objects[4];
    int field_3c;
    int field_40;
    u8 pad044[0x48];
    int field_8c;
};
struct Message12 { u32 field_00; u16 field_04, field_06; u32 field_08; };
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */
typedef struct { u16 id; u8 kind; u8 field_03; } MsgHeader;
typedef struct { MsgHeader hdr; u8 amount; Fx24 pos[3]; } ImpactMsg;

extern int func_ov107_020c5af8(struct Obj *, int, int, const FxVec *);
extern int func_ov107_020c89e8(struct Obj *, struct HitPacket *);
extern struct Manager *OS_IsThreadAvailable_0x020c9848(void);
extern int FX_Inv_0x01ff8a40(int);
extern void func_01ffa724(int, VecFx32 *, VecFx32 *);
extern u32 func_02023eb4(u32);
extern int func_02020400(int, int);
extern u16 func_02031384(int, const void *, u16);
/* Both templates are within ov107's .rodata range. */
struct FourBytes { u8 bytes[4]; };
struct ReactionConstants { struct FourBytes masks, values; u8 field_08[8]; };
extern const struct ReactionConstants data_ov107_020cb628;
extern const struct Message12 data_ov107_020cb64c;


static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}
static inline void PackFx24(Fx24 *dst, int v)
{
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}
static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

/* Validate a hit, dispatch the object's handler, then update reactions and notifications. */
int func_ov107_020c5cfc(struct Obj *obj, struct HitSource *source, struct HitPacket *packet)
{
    /* Preserve the field's signed 16-bit type. An int reverses the save/source stores. */
    short previousAmount;
    int amount;
    int i;
    int maximum;
    int after;
    int before;
    int accumulated;

    if (obj->header.extra.field_50 != 1) return 0;
    if (((u32)(obj->header.ai.flags60 << 24) >> 24 & 1) == 0) return 0;
    if (packet == 0) return 0;
    if (packet->field_1c < 0 || packet->field_1c > 100) return 0;
    if (obj->field_2e4 > 0) return 0;
    if (obj->field_1ac & 1) return 0;
    if (obj->field_1c4 & 0x10) {
        if ((packet->flagsLo & 4) && !(packet->flagsLo & 8) && source != 0) {
            func_ov107_020c5af8(obj, 0, 0x3f, &obj->header.extra.field_74);
        }
        packet->flags24Lo = 1;
        packet->field_28 = 0;
        return 1;
    }
    packet->flags24Lo = 0;
    packet->field_28 = 0;
    packet->field_20 = -1;
    amount = func_ov107_020c89e8(obj, packet);
    const struct Obj *protectedObject = obj;
    if (protectedObject->field_1ac & 0x100) {
        int kind = protectedObject->field_179;
        if (kind == 1 || (u32)kind == 2) {
            if (obj->field_21a - amount <= 0) return 0;
        }
    }
    if (obj->field_1ac & 0x100) {
        if (obj->field_21a - amount <= 0) {
            packet->field_28 = 0;
            return 1;
        }
    }
    previousAmount = obj->field_21a;
    obj->field_25c = source;
    if (packet->field_14 >= 0) {
        obj->field_258 = packet->field_14;
        if (source != 0 && source->field_1c8 != 0) {
            obj->field_254 = source->field_1c8(packet->field_14)->field_0c;
        }
    }
    if (!(obj->field_1ac & 0x40) && !(packet->flagsLo & 0x80)) {
        if (((((obj->field_1ac & 0x20) && (packet->flagsLo & 0x20)) ||
               !(obj->field_1ac & 0x20) || (packet->flagsLo & 0x2008)) && amount > 0) ||
            (!(obj->field_1ac & 0x60) && (packet->flagsLo & 0x800))) {
            packet->flagsLo |= 0x8000;
        }
    }
    if (obj->field_1a0 != 0 && (packet->flagsLo & 8) && (packet->flagsHi & 4)) {
        packet->normal.y = FX_Mul(packet->normal.y, obj->field_1a0->field_64 << 4);
    }
    if (obj->field_1d0 != 0) {
        VecFx32 savedNormal;
        savedNormal = packet->normal;
        func_01ffa724(FX_Inv_0x01ff8a40(OS_IsThreadAvailable_0x020c9848()->field_40),
                      &packet->normal, &packet->normal);
        if (obj->field_1d0(obj, source, packet) != 0) {
            packet->normal = savedNormal;
            if (packet->field_28 >= 0 || (packet->flagsLo & 0x10)) {
                if (!(obj->field_1ac & 4) && (packet->flagsHi & 0x88c)) {
                    u8 masks[4] = {7, 3, 11, 2};
                    u8 values[4] = {1, 2, 4, 8};
                    u8 selected[4] = {0};
                    int count = 0;
                    for (i = 0; i < 4; i++) {
                        int chance = packet->field_1c << 12;
                        if ((packet->flagsHi & (1 << masks[i])) &&
                            !(obj->field_1b0 & (1 << masks[i])) && !(values[i] & obj->field_1c4)) {
                            chance = FX_Mul(chance, 0x1000 - obj->field_1b4[i]);
                            if (chance < 0) chance = 0;
                            if (chance > 0x64000) chance = 0x64000;
                            if (RandRange(0x1000, 0x64000) <= chance) {
                                selected[count++] = values[i];
                            }
                        }
                    }
                    if (count > 0) {
                        int reaction = selected[RandRange(0, count - 1)];
                        obj->field_1c5 &= ~0xf;
                        obj->field_1c5 |= reaction;
                        switch (reaction) {
                        case 1:
                            obj->field_2e0 = 0xc000;
                            obj->field_2dc = 0x800;
                            obj->field_2de = 0;
                            break;
                        case 2:
                            obj->field_2e0 = 0x5000;
                            break;
                        case 4:
                            obj->field_2e0 = 0xf000;
                            obj->field_2f0 = 0x1000;
                            break;
                        case 8:
                            obj->field_2e0 = 0x6000;
                            if (obj->field_1a0 == 0) obj->field_2ec = 0x1000;
                            else obj->field_2ec = FX_Mul(0x1000, obj->field_1a0->field_64 << 4);
                            break;
                        }
                    }
                } else {
                    if (packet->field_28 != 0 || !(packet->flagsLo & 0x80)) {
                        if ((obj->field_1c4 & 2) && (packet->flagsLo & 0x28)) {
                            obj->field_1c5 &= ~2;
                        } else if ((obj->field_1c4 & 8) && (packet->flagsLo & 0x20)) {
                            obj->field_1c5 &= ~8;
                        }
                    }
                }
            } else if (packet->field_28 < 0) {
                struct Message12 message;
                message = data_ov107_020cb64c;
                message.field_04 = obj->header.extra.field_02;
                if (obj->header.ai.field_24 != 0) {
                    ((void (*)(struct Obj *, void *, int))obj->header.ai.field_24)(obj, &message, 12);
                }
            }
            if (obj->field_218 > 0) {
                maximum = obj->field_218;
                accumulated = 0;
                before = func_02020400(previousAmount << 12, maximum);
                after = func_02020400(obj->field_21a << 12, maximum);
                for (i = 0; i < 5; i++) {
                    if (obj->field_314[i].field_00 >= 0 && obj->field_314[i].field_04 > 0 &&
                        obj->field_314[i].field_08 > 0 && obj->field_1a0 != 0 &&
                        before > obj->field_314[i].field_00 && obj->field_314[i].field_00 >= after &&
                        RandRange(0, 0x1000) <= obj->field_314[i].field_04) {
                        struct Manager *manager = OS_IsThreadAvailable_0x020c9848();
                        accumulated += FX_Mul(FX_Mul(obj->field_1a0->field_50 * obj->field_314[i].field_08,
                                                      manager->field_8c), obj->field_2f8);
                    }
                }
                if (accumulated > 0x800) {
                    FxVec position;
                    ImpactMsg event = {0};
                    MsgHeader *hdr = (MsgHeader *)&event;
                    Fx32 z;
                    Fx32 y;
                    Fx32 x;
                    position = obj->header.extra.field_74;
                    position.y.value += obj->header.ai.field_80;
                    hdr->id = obj->header.extra.field_02;
                    hdr->kind = 11;
                    event.amount = (accumulated + 0x800) >> 12;
                    x = position.x;
                    PackFx24(&event.pos[0], x.value);
                    y = position.y;
                    PackFx24(&event.pos[1], y.value);
                    z = position.z;
                    PackFx24(&event.pos[2], z.value);
                    func_02031384(4, &event, sizeof(ImpactMsg));
                }
            }
            if (obj->field_21a == 0) {
                if (obj->field_179 == 1) {
                    for (i = 0; i < 4; i++) {
                        struct Manager *manager = OS_IsThreadAvailable_0x020c9848();
                        struct Obj *observer = manager != 0 ? manager->objects[i] : 0;
                        if (observer != 0 && observer->field_1d4 != 0) {
                            observer->field_1d4(observer, obj);
                        }
                    }
                }
                packet->flags24Lo |= 2;
            }
            return 1;
        }
    }
    return 0;
}

