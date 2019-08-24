#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "section.h"
#include "elf.h"

static void print_section_headers(section_header **hdrs)
{
    int i;

    for (i = 0; hdrs[i]; i++)
    {
        /* printf("Type:%08x, Offset:%08lx, Filesz:%08lx,Memsz:%08lx, Align:%08lx, Paddr:%08lx, Vaddr:%08lx, Flags:%08x\n", */
               /* hdrs[i]->p_type, */
               /* hdrs[i]->p_offset, */
               /* hdrs[i]->p_filesz, */
               /* hdrs[i]->p_memsz, */
               /* hdrs[i]->p_align, */
               /* hdrs[i]->p_paddr, */
               /* hdrs[i]->p_vaddr, */
               /* hdrs[i]->p_flags); */
    }
}

section_header **get_section_headers(FILE *fp, uint16_t e_shnum)
{
    int i;
    section_header **hdrs = (section_header **)malloc(sizeof(section_header *) * e_shnum);

    for (i = 0; i < e_shnum; i++)
    {
        hdrs[i] = (section_header *)malloc(sizeof(section_header) + 1);
        if (fgets((char *)(hdrs[i]), sizeof(section_header) + 1, fp) == NULL)
            return NULL;
    }
    hdrs[i] = NULL;
    print_section_headers(hdrs);
    return hdrs;
}
