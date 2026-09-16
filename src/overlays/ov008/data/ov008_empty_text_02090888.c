/* data_ov008_02090888: the empty kind text 0206ff24 falls back to.
 * Zero bytes in .data: mwcc would move a zero initialiser to .bss without
 * the explicit_zero_data pragma.
 */
#pragma explicit_zero_data on
char data_ov008_02090888[4] = "";
#pragma explicit_zero_data off
