extern void *NNS_FndGetNextListObject(void *list, void *object);

void *func_ov008_020565bc(void *object, void *start)
{
    void *entry = NNS_FndGetNextListObject((char *)object + 0x18, start);

    while (entry != 0) {
        if (*(int *)((char *)entry + 0x10) == 0) {
            break;
        }

        entry = NNS_FndGetNextListObject((char *)object + 0x18, entry);
    }

    return entry;
}
