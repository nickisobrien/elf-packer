#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "elf.h"

int is_elf(elf_header *hdr)
{
    if (hdr->e_ident[0] != 0x7f)
        return 0;
    if (strncmp((char *)hdr->e_ident+1, ELF_MAG_HEADER, 3))
        return 0;
    return 1;
}

elf_header *get_elf_header(FILE *fp)
{
    elf_header *hdr = (elf_header *)malloc(sizeof(elf_header));
    if (fgets((char *)hdr, ELF_HDR_SIZE, fp) == NULL)
        return NULL;
    return hdr;
}

