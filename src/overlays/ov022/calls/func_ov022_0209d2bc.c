typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned long long u64;

typedef struct Ov022BattleObject {
    u8 pad000[0x464];
    u64 flags464;
    u8 pad46c[0x228];
    u8 flags694;
    u8 pad695[0x13f];
    u16 animation7d4;
    u8 pad7d6[0x106];
    s16 timer8dc;
} Ov022BattleObject;

extern u8 func_ov022_020882bc(int entityId);
extern int func_ov002_0205766c(int entityIndex);
extern int func_0202a818(u16 *timer, int amount);
extern int data_0204c240;

void func_ov022_0209d2bc(Ov022BattleObject *object, int amount) {
    if ((*(u8 *)&data_0204c240 & 4) == 0) {
        return;
    }
    func_ov002_0205766c(func_ov022_020882bc(*((u8 *)object + 9)));
    if ((object->flags464 & 0x8000000000000ULL) != 0) {
        object->timer8dc = 0x6000;
        func_0202a818(&object->animation7d4, amount);
        object->flags694 |= 0x10;
        return;
    }
    if (object->timer8dc > 0) {
        object->timer8dc -= (s16)amount;
        if (object->timer8dc <= 0) {
            object->timer8dc = 0;
        }
    }
    if ((((unsigned int)object->flags694) << 0x1b) >> 0x1f) {
        if (func_0202a818(&object->animation7d4, amount) != 0) {
            if (object->timer8dc == 0) {
                object->flags694 &= ~0x10;
            }
        }
    }
}
