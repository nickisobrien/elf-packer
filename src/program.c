#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "program.h"
#include "elf.h"

static void print_program_headers(program_header **hdrs)
{
    int i;

    for (i = 0; hdrs[i]; i++)
    {
        printf("Type:%08x, Offset:%08lx, Filesz:%08lx,Memsz:%08lx, Align:%08lx, Paddr:%08lx, Vaddr:%08lx, Flags:%08x\n",
               hdrs[i]->p_type,
               hdrs[i]->p_offset,
               hdrs[i]->p_filesz,
               hdrs[i]->p_memsz,
               hdrs[i]->p_align,
               hdrs[i]->p_paddr,
               hdrs[i]->p_vaddr,
               hdrs[i]->p_flags);
    }
}

program_header **get_program_headers(FILE *fp, uint16_t e_phnum)
{
    int i;
    program_header **hdrs = (program_header **)malloc(sizeof(program_header *) * e_phnum);

    for (i = 0; i < e_phnum; i++)
    {
        hdrs[i] = (program_header *)malloc(sizeof(program_header) + 1);
        if (fgets((char *)(hdrs[i]), sizeof(program_header) + 1, fp) == NULL)
            return NULL;
    }
    hdrs[i] = NULL;
    print_program_headers(hdrs);
    return hdrs;
}
