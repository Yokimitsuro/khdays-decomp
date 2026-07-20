/* OS_IsTickAvailable: returns the tick-availability flag held at data_02044664. */

extern unsigned short data_02044664;

int OS_IsTickAvailable_0x0200315c(void) {
    return data_02044664;
}
