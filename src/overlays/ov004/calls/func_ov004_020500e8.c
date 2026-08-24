typedef long long s64;
typedef unsigned int u32;

typedef void (*OSAlarmHandler)(void *arg);

typedef struct OSAlarm {
    OSAlarmHandler handler;
    void *arg;
    u32 pad_08[5];
    s64 period;
    s64 fire;
} OSAlarm;

typedef struct Ov004Context {
    char pad_0000[0x55ec];
    OSAlarm alarm;
} Ov004Context;

extern Ov004Context *data_ov004_02051384;

extern void func_02003380(void);
extern void OS_CreateAlarm(OSAlarm *alarm);
extern s64 func_020031d4(void);
extern void func_020035a8(OSAlarm *alarm, s64 fire, s64 period,
                          OSAlarmHandler handler, void *arg);

void func_ov004_020500e8(void *arg) {
    register char *alarmBase;
    s64 tick;
    s64 fire;

    if (data_ov004_02051384->alarm.handler != 0) {
        return;
    }

    func_02003380();
    OS_CreateAlarm(&data_ov004_02051384->alarm);
    tick = func_020031d4();
    fire = tick + 0x7fd88LL;
    alarmBase = (char *)data_ov004_02051384 + 0x1ec;
    func_020035a8((OSAlarm *)(alarmBase + 0x5400), fire, 0x7fd88,
                  func_ov004_020500e8, 0);
}

