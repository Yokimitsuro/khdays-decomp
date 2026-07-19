/* Looks the id up in a length-prefixed chain of variable-size records; returns the record's
 * value field, or -1 when it is not there. */
int func_ov069_020b815c(char *table, int id) {
    unsigned short count = *(unsigned short *)table;
    unsigned short i;
    table += 2;
    i = 0;
    while (i < count) {
        if (*(unsigned short *)(table + 2) == (unsigned short)id) {
            return *(unsigned short *)(table + 4);
        }
        table += *(unsigned short *)table;
        i = (unsigned short)(i + 1);
    }
    return -1;
}
