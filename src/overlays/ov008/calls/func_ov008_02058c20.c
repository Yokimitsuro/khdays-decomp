typedef unsigned char u8;

struct Ov008MenuRenderer {
    u8 field00[4];
    u8 variables[0x48];
    u8 surface[0x40];
    void *handle8c;
    void *handle90;
};

extern int func_ov008_02050c54(void);
extern int func_020235d0(int field, int index);
extern int func_02023588(int flag);
extern int func_ov008_02054788(int context, int id);
extern void func_ov008_02054b18(int context, int entry, int value);
extern void *func_ov008_02055c84(void *variables, int index);
extern void func_02030158(void *surface);
extern void func_02030278(void *surface, int id, int x, int y,
                          void *buffer, int flags);
extern void func_020300f8(void *surface);

int
func_ov008_02058c20(struct Ov008MenuRenderer *renderer)
{
    int result;
    int hasHandle;
    int hasLevel8;
    int hasAnyFlag;
    int i;
    int context;
    int level;
    int category;
    void *buffer;

    result = 0;
    hasHandle = result;
    hasLevel8 = result;
    hasAnyFlag = result;
    context = func_ov008_02050c54();
    level = func_020235d0(0, 9);

    for (i = 0; i < 0x39; i++) {
        if (func_02023588(i + 0x3c2b) != 0) {
            hasAnyFlag = 1;
            break;
        }
    }

    if (hasAnyFlag == 0) {
        func_ov008_02054b18(context,
                            func_ov008_02054788(context, 4), 1);
    }

    if (level >= 8) {
        hasLevel8 = 1;
    } else {
        func_ov008_02054b18(context,
                            func_ov008_02054788(context, 3), 1);
    }

    if (level >= 11) {
        result = 1;
    }
    if (result == 0) {
        func_ov008_02054b18(context,
                            func_ov008_02054788(context, 1), 1);
    }

    if (renderer->handle8c != 0 || renderer->handle90 != 0) {
        hasHandle = 1;
    } else {
        func_ov008_02054b18(context,
                            func_ov008_02054788(context, 2), 1);
    }

    if (result != 0) {
        category = 1;
        buffer = func_ov008_02055c84(renderer->variables, 9);
    } else if (hasHandle != 0) {
        category = 2;
        buffer = func_ov008_02055c84(renderer->variables, 10);
    } else if (hasLevel8 != 0) {
        category = 3;
        buffer = func_ov008_02055c84(renderer->variables, 12);
    } else if (hasAnyFlag != 0) {
        category = 4;
        buffer = func_ov008_02055c84(renderer->variables, 15);
    } else {
        category = 5;
        buffer = func_ov008_02055c84(renderer->variables, 11);
    }

    func_02030158(renderer->surface);
    func_02030278(renderer->surface, 0x56, 0, 2, buffer, 0);
    func_020300f8(renderer->surface);
    return category;
}
