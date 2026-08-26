typedef unsigned int u32;

typedef struct Ov022SelectionPoint {
    int x;
    int y;
} Ov022SelectionPoint;

typedef struct Ov022DisplayObject {
    char padding000[0x10];
    int pointX;
    int pointY;
} Ov022DisplayObject;

typedef struct Ov022StateFlags {
    u32 unknown0 : 2;
    u32 finished : 1;
    u32 unknown3 : 29;
} Ov022StateFlags;

typedef struct Ov022UiSubsystem {
    char padding000[0x120];
    Ov022DisplayObject * volatile displayObject;
    int state;
    char padding128[4];
    char tween[8];
    int tweenTarget;
    int tweenStart;
    char padding13c[8];
    Ov022StateFlags flags;
} Ov022UiSubsystem;

extern int func_ov022_02083f0c(void);
extern void func_ov002_02050e64(void);
extern void func_0203602c(void *tween, int *value);
extern void func_ov022_02086264(Ov022UiSubsystem *subsystem, int value,
                                const volatile Ov022SelectionPoint *point);
extern int func_ov002_0205127c(Ov022DisplayObject *object);
extern void func_02035fb0(void *tween, int mode, int start, int target,
                          int duration);
extern void func_02035ffc(void *tween);
extern void func_ov000_0204cac0(int object, int mode);

void func_ov022_02086138(Ov022UiSubsystem *subsystem,
                         const volatile Ov022SelectionPoint *point)
{
    int value;
    int object = func_ov022_02083f0c();

    func_ov002_02050e64();
    switch (subsystem->state) {
    case 1:
    {
        Ov022DisplayObject *displayObject;
        int pointX;
        int pointY;

        func_0203602c(subsystem->tween, &value);
        func_ov022_02086264(subsystem, value, point);
        displayObject = subsystem->displayObject;
        pointX = point->x;
        pointY = point->y;
        displayObject->pointX = pointX;
        displayObject->pointY = pointY;
        func_ov002_0205127c(subsystem->displayObject);
        if (subsystem->flags.finished) {
            func_02035fb0(subsystem->tween, 0, 0, 0x5000, 0x12c);
            func_02035ffc(subsystem->tween);
            subsystem->state = 2;
        }
        break;
    }
    case 2:
    {
        Ov022DisplayObject *displayObject;
        int pointX;
        int pointY;

        func_0203602c(subsystem->tween, &value);
        func_ov022_02086264(subsystem, value, point);
        displayObject = subsystem->displayObject;
        pointX = point->x;
        pointY = point->y;
        displayObject->pointX = pointX;
        displayObject->pointY = pointY;
        func_ov002_0205127c(subsystem->displayObject);
        if (subsystem->flags.finished) {
            func_02035fb0(subsystem->tween, 0, subsystem->tweenStart,
                          subsystem->tweenTarget, 0x12c);
            func_02035ffc(subsystem->tween);
        }
        break;
    }
    }
    func_ov000_0204cac0(object, 0);
}
