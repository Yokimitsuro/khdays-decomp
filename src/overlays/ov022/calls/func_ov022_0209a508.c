typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Ov022Actor {
    u64 statusFlags;
    u8 pad008;
    u8 actorId;
    u8 pad00a[8];
    u16 currentHp;
} Ov022Actor;

typedef struct Ov022ActionContext {
    u8 pad000[0x18c];
    Ov022Actor *actor;
} Ov022ActionContext;

extern int func_02035924(int actorId);
extern void func_ov022_020aa824(Ov022Actor *actor, int parameter,
                                int amount, int enabled);
extern int func_ov022_020882f8(void);
extern Ov022Actor *func_01fffde0(int index);
extern int func_ov022_020ad61c(Ov022Actor *actor, int amount);

u32 func_ov022_0209a508(Ov022ActionContext *context, int parameter,
                        int action, int amount) {
    Ov022Actor *actor = context->actor;
    u32 result = 1;
    int i;

    if (actor->currentHp == 0) {
        goto returnZero;
    }
    i = 0;
    if ((actor->statusFlags & 0x20000ULL) != 0) {
        goto returnZero;
    }
    if ((actor->statusFlags & 0x100ULL) != 0) {
        goto returnZero;
    }
    goto dispatch;

returnZero:
    return 0;

dispatch:
    switch (action) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        if (func_02035924(actor->actorId) != 0) {
            result = 0;
        } else {
            func_ov022_020aa824(actor, parameter, amount, result);
        }
        break;
    case 13:
        if (func_ov022_020882f8() > 0) {
            do {
                if (func_ov022_020ad61c(func_01fffde0(i), amount) != 0) {
                    result = 0;
                    goto done;
                }
                i++;
            } while (i < func_ov022_020882f8());
        }
        break;
    case 14:
        break;
    }

done:
    return result;
}
