typedef struct Ov022DisplayRecord {
    char pad00[4];
    unsigned short width;
    unsigned short height;
    unsigned int attributes;
    char pad0c[0x18];
    unsigned char alpha;
    char pad25[0xb];
} Ov022DisplayRecord;

typedef struct Ov022DisplayGroup {
    Ov022DisplayRecord records[3];
    char tween[0x1c];
} Ov022DisplayGroup;

extern int func_020255d4(int *list, int group, int index);
extern void func_ov002_02050d28(Ov022DisplayRecord *record, int resource, int mode);
extern void func_02035f84(void *tween);

void func_ov022_02086318(Ov022DisplayGroup *group, int *list)
{
    int resource;

    resource = func_020255d4(list, 7, 0);
    func_ov002_02050d28(&group->records[0], resource, 1);
    resource = func_020255d4(list, 7, 1);
    func_ov002_02050d28(&group->records[1], resource, 1);
    resource = func_020255d4(list, 7, 5);
    func_ov002_02050d28(&group->records[2], resource, 1);

    group->records[0].width = 0x10;
    group->records[0].height = 0x10;
    group->records[1].width = 0x20;
    group->records[1].height = 0x20;
    group->records[2].width = 0x40;
    group->records[2].height = 0x40;

    group->records[0].attributes |= 0xa << 16;
    group->records[1].attributes |= 0xf << 16;
    group->records[2].attributes |= 0xf << 16;

    group->records[0].alpha = 0x3f;
    group->records[1].alpha = 0x3f;
    group->records[2].alpha = 0x3e;

    func_02035f84(group->tween);
}
