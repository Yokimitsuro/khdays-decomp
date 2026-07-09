extern void *NNS_FndGetNextListObject(void *list, void *object);

void *func_ov008_020566ac(void *context)
{
    void *entry = NNS_FndGetNextListObject((char *)context + 0x18, 0);

    while (entry != 0) {
        if (*(int *)((char *)entry + 0x10) > 0) {
            break;
        }
        entry = NNS_FndGetNextListObject((char *)context + 0x18, entry);
    }

    return entry;
}
