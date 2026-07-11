/* Find node[0]==key in the list at obj[0x2c] (next at +0xc); on a hit copy
 * node[4]/[8]/[0xc] into obj[0x24]/[0x28]/[0x2c] and return 1, else 0. */
int func_02010c7c(int *obj, int key) {
    int *node = (int *)obj[0xb];
    if (key != 0 && node != 0) {
        do {
            if (node[0] == key) break;
            node = (int *)node[3];
        } while (node != 0);
    }
    if (node == 0) return 0;
    obj[9] = node[1];
    obj[0xa] = node[2];
    obj[0xb] = node[3];
    return 1;
}
