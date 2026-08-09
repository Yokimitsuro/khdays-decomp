/* OS_InitIrqTable: clears the two-word IRQ table at data_027e006c. */

extern int data_027e006c;

void OS_InitIrqTable(void) {
    *(int *)((int)&data_027e006c + 4) = 0;
    data_027e006c = 0;
}
