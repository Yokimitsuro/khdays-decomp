typedef unsigned char u8;
typedef signed short s16;
typedef unsigned long long u64;

typedef struct Ov022ActiveActor {
    u64 flags0;
    char pad_0008[0x45c];
    u64 flags464;
} Ov022ActiveActor;

typedef struct Ov022SelectionController {
    unsigned int flags0;
    unsigned int selectionFlags;
    int type;
    char pad_000c[0x14];
    int scanDistance;
    int selectedIndex;
    int selectedValue;
    int runtimeMode;
    int repeat100;
    int repeat200;
    int repeatAny;
    char pad_003c[0x1f4];
    int activationState;
} Ov022SelectionController;

extern u8 data_0204be04;
extern s16 data_0204c18c;
extern s16 data_0204c190;
extern u8 data_ov022_020b2e6c;

extern int func_ov022_02083f0c(void);
extern Ov022SelectionController *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov022_020881d8(void);
extern int func_ov022_0208868c(void);
extern void func_ov022_020848bc(void *state, int mask);
extern void func_ov002_02056a98(int mode);
extern void func_ov002_02056b70(void);
extern int func_02030670(void);
extern int func_02030694(void);
extern int func_020208e0(void);
extern int func_01fffe14(void);
extern Ov022ActiveActor *func_01fffde0(int index);
extern void func_ov022_020852c0(int enabled);
extern int func_ov022_02088338(void);
extern void func_ov022_02085d00(void);
extern int func_020358f4(int index, int parameter);
extern int func_ov022_02084fe8(void *state, int actorIndex);
extern void func_ov022_0208471c(void);
extern void func_ov022_02085858(void);
extern void func_ov022_02085280(void);
extern int func_020235d0(int value, int mode);
extern void *func_ov022_020840fc(int mask);
extern int func_ov002_0205e430(void);
extern int func_ov002_0204cb40(int object);
extern int func_02023c40(void);
extern void func_ov000_0204cac0(int object, int mode);

int func_ov022_02085380(void)
{
    int object = func_ov022_02083f0c();
    Ov022SelectionController *context = NNSi_FndGetCurrentRootHeap();
    u8 runtimeMode = data_0204be04;
    s16 held;
    s16 pressed;
    int suppressInput;
    Ov022ActiveActor *actor;
    int step;
    int value;

    held = data_0204c18c;
    pressed = data_0204c190;
    suppressInput = 0;
    if (runtimeMode != context->runtimeMode) {
        return suppressInput;
    }
    if (func_ov022_020881d8() != 0) {
        return suppressInput;
    }
    if (func_ov022_0208868c() != 0) {
        context->flags0 &= ~4;
        func_ov022_020848bc(&context->selectionFlags, 2);
        func_ov002_02056a98(suppressInput);
        func_ov002_02056b70();
        return suppressInput;
    }
    if ((context->flags0 & 8) != 0) {
        return suppressInput;
    }
    if ((context->flags0 & 0x20) == 0) {
        suppressInput = 1;
    }
    if (func_02030670() != 0 && func_02030694() != 0 &&
        func_020208e0() == 2) {
        suppressInput = 1;
    }
    if (suppressInput != 0) {
        held = 0;
        pressed = 0;
    }

    actor = func_01fffde0(func_01fffe14());
    if ((actor->flags0 & 0x800ULL) != 0 ||
        (actor->flags464 & 0x400ULL) != 0) {
        if ((context->flags0 & 4) != 0) {
            func_ov022_020852c0(0);
        }
        func_ov022_020848bc(&context->selectionFlags, 2);
        return 0;
    }
    if (func_ov022_02088338() == 0) {
        func_ov022_02085d00();
        return 0;
    }

    context->scanDistance = 0x9000;
    context->selectedIndex = -1;
    context->selectedValue = 0;
    if (func_020358f4(func_01fffe14(), 0x55) != 0) {
        context->scanDistance =
            (int)(((long long)context->scanDistance * 0x1800 + 0x800) >> 12);
    }

    if ((context->flags0 & 4) == 0) {
        actor = func_01fffde0(func_01fffe14());
        if ((actor->flags464 & 0x10ULL) == 0 || context->type != 1) {
            if (func_ov022_02084fe8(&context->selectionFlags,
                                    func_01fffe14()) != 0) {
                func_ov022_0208471c();
            } else {
                func_ov022_020852c0(0);
            }
        }
    }

    if (data_ov022_020b2e6c != 0) {
        if ((held & 0x100) == 0) {
            goto clear_runtime_latch;
        }
        if ((held & 0x200) != 0) {
            goto keep_runtime_latch;
        }
clear_runtime_latch:
        data_ov022_020b2e6c = 0;
    }
keep_runtime_latch:
    if (data_0204be04 != 0) {
        return 0;
    }

    func_ov022_02085858();
    if ((context->flags0 & 4) != 0) {
        suppressInput = pressed & 0x100;

        if (suppressInput != 0) {
            if (context->repeatAny < 0x9000) {
                if (context->activationState == 0) {
                    func_ov022_020852c0(0);
                } else {
                    func_ov022_02085280();
                }
            }
            context->repeatAny = 0;
        }

        if ((context->flags0 & 4) != 0 && context->activationState == 0) {
            if (func_020235d0(0x37c4, 1) == 0) {
                if (suppressInput != 0) {
                    if (func_ov022_020840fc(0x100) != 0) {
                        func_ov022_020852c0(1);
                    } else {
                        int attempts = 30;
                        while (func_ov022_020840fc(0x200) != 0 &&
                               attempts > 0) {
                            context->scanDistance = 0x9000;
                            context->selectedIndex = -1;
                            context->selectedValue = 0;
                            attempts--;
                        }
                        func_ov022_020852c0(1);
                    }
                }
            } else if (func_ov002_0205e430() == 0) {
                if (suppressInput != 0) {
                    context->repeat100 = 0;
                }
                if (context->repeat100 < 0x9000 &&
                    (held & 0x100) == 0) {
                    context->repeat100 = 0xf000;
                    func_ov022_020840fc(0x100);
                    func_ov022_020852c0(1);
                }
                if ((pressed & 0x200) != 0) {
                    context->repeat200 = 0;
                }
                if (context->repeat200 < 0x9000 &&
                    (held & 0x200) == 0) {
                    context->repeat200 = 0xf000;
                    func_ov022_020840fc(0x200);
                    func_ov022_020852c0(1);
                }
            }
        }
    } else if (func_ov002_0204cb40(object) == 0) {
        if ((pressed & 0x100) != 0) {
            if (context->repeatAny < 0x9000) {
                func_ov022_02085280();
            }
            context->repeatAny = 0;
        }
        if ((context->flags0 & 4) == 0 &&
            func_020358f4(func_01fffe14(), 0x54) != 0) {
            actor = func_01fffde0(func_01fffe14());
            if ((actor->flags464 & 0x10ULL) != 0 ||
                (actor->flags464 & 0x1000ULL) != 0) {
                func_ov022_02085280();
            }
        }
    }

    step = func_02023c40() == 1 ? 0x1800 : 0x1000;

    value = context->repeat100 + step;
    if (value > 0xf000) {
        value = 0xf000;
    } else if (value < 0) {
        value = 0;
    }
    context->repeat100 = value;

    value = context->repeat200 + step;
    if (value > 0xf000) {
        value = 0xf000;
    } else if (value < 0) {
        value = 0;
    }
    context->repeat200 = value;

    value = context->repeatAny + step;
    if (value > 0xf000) {
        value = 0xf000;
    } else if (value < 0) {
        value = 0;
    }
    context->repeatAny = value;

    func_ov022_02085d00();
    func_ov000_0204cac0(object, 0);
    return 0;
}
