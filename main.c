
#include <stdio.h>

/*
#include <stddef.h>
#include <stdint.h>
*/


#include <graphics/gfxbase.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/graphics.h>
#include <proto/intuition.h>

/* extern int test(void); */

/*
#define COP1LCH   0xDFF080
#define COP1LCL   0xDFF082
#define COP2LCH   0xDFF084
#define COP2LCL   0xDFF086

struct CopperLists {
    uint32_t copperlist1;
    uint32_t copperlist2;
}

void SaveCopperList(struct CopperLists* copperlists) {
    uint32_t *copperlist1 = (uint32_t *)COP1LCH;
    uint32_t *copperlist2 = (uint32_t *)COP2LCH;
    copperlists->copperlist1 = *copperlist1;
    copperlists->copperlist2 = *copperlist2;
}

void LoadCopperList(const struct CopperLists* copperlists) {
    uint32_t *copperlist1 = (uint32_t *)COP1LCH;
    uint32_t *copperlist2 = (uint32_t *)COP2LCH;
    *copperlist1 = copperlists->copperlist1;
    *copperlist2 = copperlists->copperlist2;
}

*/

//#define printf(x) Write(Output(), x, sizeof(x))

// Global variables as they are accessed from outside
//struct Library *SysBase;
struct GfxBase *GfxBase = NULL;
struct IntuitionBase *IntuitionBase = NULL;

// Already opened using startup.o
//struct DosLibrary *DOSBase = NULL;

extern struct ExecBase *SysBase;

int main(void) {
    APTR active_view;
    APTR copperlist1;
    APTR copperlist2;
    const char *graphics_library = "graphics.library";
    //const char *dos_library = "dos.library";
    const char *intuition_library = "intuition.library";
    //struct Library *SysBase;

    SysBase = *((struct ExecBase **)4L);

    //int *test = 4L;

    // DOSBase = (struct DosLibrary *)OpenLibrary(dos_library, 0);
    // if (DOSBase == NULL) {
    //     printf("Error opening dos library. Exiting.");
    //     goto exit;
    // }

    GfxBase = (struct GfxBase *)OpenLibrary(graphics_library, 0);
    if (GfxBase == NULL) {
        printf("Error opening graphics library. Exiting.");
        goto exit;
    }

    IntuitionBase = (struct IntuitionBase *)OpenLibrary(intuition_library, 0);
    if (IntuitionBase == NULL) {
        printf("Error opening intuition library. Exiting.");
        goto exit;
    }

    //printf("test: %x\n", test);

    active_view = GfxBase->ActiView;
    copperlist1 = GfxBase->copinit;
    copperlist2 = GfxBase->LOFlist;

    LoadView(NULL);

    WaitTOF();
    WaitTOF();

    //custom->cop1lc = (ULONG)oldCopinit;

    LoadView((struct View *)active_view);

    WaitTOF();
    WaitTOF();

    RethinkDisplay();
    
exit:
    if (IntuitionBase) {
        CloseLibrary((struct Library *)IntuitionBase);
    }

    if (GfxBase) {
        CloseLibrary((struct Library *)GfxBase);
    }

    return 0;
}