/*
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
*/

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/graphics.h>

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

int main(void) {
    const char *graphics_library = "graphics.library";
    const char *dos_library = "dos.library";
    struct Library *SysBase;
    struct GfxBase *gfx_base = NULL;
    struct DosLibrary *dos_base = NULL;

    SysBase = *((struct Library **)4L);

    dos_base = (struct DosLibrary *)OpenLibrary(dos_library, 0);
    if (dos_base == NULL) {
        Write(Output(), "Hello, world!", 14);
        goto exit;
    }

    gfx_base = (struct GfxBase *)OpenLibrary(graphics_library, 0);
    if (gfx_base == NULL) {
        Write(Output(),"Hello, world!\n", 14); 
        /* printf("Error opening graphics library\n"); */
        goto exit;
    }
    
    /*
    result = test();

    printf("Hello World: %i\n", result);
    */
exit:
    if (gfx_base) {
        CloseLibrary((struct Library *)gfx_base);
    }

    if (dos_base) {
        CloseLibrary((struct Library *)dos_base);
    }

    return 0;
}