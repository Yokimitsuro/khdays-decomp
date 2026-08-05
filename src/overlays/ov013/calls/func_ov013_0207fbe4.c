typedef struct {
    char padding00[0x108];
    unsigned char flags;
    signed char state;
    char padding10a[2];
} Ov013Record;

typedef struct {
    char padding00[0x110];
    signed char count;
    char padding111[3];
    Ov013Record records[];
} Ov013RecordList;

extern char data_ov013_0207fec0[];
extern void func_ov002_02072aa0(void *data, int kind, int zero, int value);

void func_ov013_0207fbe4(void *unused, int value, Ov013RecordList *list) {
    int i = 0;

    if (list->count > 0) {
        Ov013Record *record = list->records;
        do {
            if (record->state == 1) {
                record->flags &= ~1;
                break;
            }
            i++;
            record++;
        } while (i < list->count);
    }

    func_ov002_02072aa0(data_ov013_0207fec0, 5, 0, value);
}

