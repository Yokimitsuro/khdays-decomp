/* Installs the alarm handler and pushes sound command 0x12 with the generation tag. */
extern int SNDi_SetAlarmHandler(int id, void *fn, void *arg);
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SND_SetupAlarm(int id, int tick, int period, void *fn, void *arg) {
    int gen = SNDi_SetAlarmHandler(id, fn, arg);
    PushCommand_impl(0x12, id, tick, period, gen);
}
