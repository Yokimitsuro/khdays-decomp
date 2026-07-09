extern void *NNS_FndGetNextListObject(void *list, void *object);

int func_ov008_02053a54(void *object)
{
    int count = 0;
    void *entry = NNS_FndGetNextListObject((char *)object + 0x20, 0);

    while (entry != 0) {
        count++;
        entry = NNS_FndGetNextListObject((char *)object + 0x20, entry);
    }

    return count;
}
