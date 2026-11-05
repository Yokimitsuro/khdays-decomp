/* Initialises the reward menu's resource tracker and loads its sections from the result archive. */

#include "nitro/types.h"
#include "game/archive.h"

typedef int (*ResourceCallback)(int);
typedef struct Ov000ResourceTrackerConfig {u32 entryCapacity,nodeCapacity,auxiliaryCapacity;ResourceCallback entryCallback,nodeCallback;} Ov000ResourceTrackerConfig;
typedef struct Ov000ResourceTracker {char data[76];} Ov000ResourceTracker;
typedef struct Ov005Context {u32 resultArchive;char pad4[4];Ov000ResourceTracker resourceTracker;} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern int Ov005_ResourceEntryCallback(int);
extern int Ov005_ResourceNodeCallback(int);
extern void Ov005_Container_Init(Ov000ResourceTracker *,Ov000ResourceTrackerConfig *);
extern void Ov005_LoadAndInitResourceSections(Ov000ResourceTracker *,u32);
void Ov005_InitializeResourceTracker(void) {
    Ov000ResourceTrackerConfig config;
    Ov005Context *context=data_ov005_0205b80c;
    config.entryCapacity=57;
    config.nodeCapacity=1;
    config.auxiliaryCapacity=26;
    config.entryCallback=Ov005_ResourceEntryCallback;
    config.nodeCallback=Ov005_ResourceNodeCallback;
    Ov005_Container_Init(&context->resourceTracker,&config);
    Ov005_LoadAndInitResourceSections(&context->resourceTracker,ARCHIVE_HANDLE(data_ov005_0205b80c->resultArchive, 3));
}
