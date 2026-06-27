void func_0200268c(void **list, void **node)
{
    void **tail = list[0x8c / 4];

    if (tail == 0) {
        list[0x88 / 4] = node;
    } else {
        tail[0x10 / 4] = node;
    }

    node[0x14 / 4] = tail;
    node[0x10 / 4] = 0;
    list[0x8c / 4] = node;
}
