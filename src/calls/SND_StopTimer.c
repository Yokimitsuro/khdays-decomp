extern void SNDi_IncAlarmId(int n);
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SND_StopTimer(unsigned int chMask, unsigned int capMask, unsigned int alarmMask, unsigned int reserved) {
    int i;
    unsigned int mask = alarmMask;

    for (i = 0; i < 8 && mask != 0; i++, mask >>= 1) {
        if (mask & 1) {
            SNDi_IncAlarmId(i);
        }
    }

    PushCommand_impl(0xd, chMask, capMask, alarmMask, reserved);
}
