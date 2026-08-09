/* OS_IsTickAvailable: returns the tick-availability flag held at data_027e0064. */

extern unsigned short data_027e0064;

int OS_IsTickAvailable(void) {
    return data_027e0064;
}
