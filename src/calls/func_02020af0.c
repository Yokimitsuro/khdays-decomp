extern int strlen(const char *s);

/* Parse a "K:NNN" name string (K is a digit '0'-'3' selecting one of four world slots,
 * NNN is a decimal quantity) into a packed id: bit 31 set (valid), the slot's stored
 * pointer value (offset +0x48c of the slot array) folded into bits 9+, and the parsed
 * quantity in the low 9 bits. Malformed input (no ':' at name[1], or K out of range)
 * returns the name pointer itself, unchanged. */
int func_02020af0(void *world, char *name) {
    int i;
    int count;
    int quantity;
    int kind;
    int slot;
    int value;

    if (name[1] == ':' && (kind = name[0]) >= '0' && kind <= '3') {
        quantity = 0;
        slot = kind - '0';
        count = strlen(name) - 2;
        for (i = 0; i < count; i++) {
            quantity = quantity * 10 + (name[i + 2] - '0');
        }
        value = *(int *)((char *)world + slot * 4 + 0x48c);
        return (quantity & 0x1ff) | (0x80000000 | (((value + 0x8000) & 0xfffffc) << 7));
    }
    return (int)name;
}
