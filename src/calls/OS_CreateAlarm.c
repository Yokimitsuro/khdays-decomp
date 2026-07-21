/* OS_CreateAlarm: clears an alarm structure (handler at +0, next at +8). */

void OS_CreateAlarm(int *alarm) {
    alarm[0] = 0;
    alarm[2] = 0;
}
