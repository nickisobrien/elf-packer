#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "elf.h"

static void print_elf_header(elf_header *hdr)
{
    printf("Entry: %#08lx, program header: %#08lx, section header: %#08lx, section header entry size: %#08x\n",
           hdr->e_entry,
           hdr->e_phoff,
           hdr->e_shoff,
           hdr->e_shentsize
        );
}

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
    if (fgets((char *)hdr, sizeof(elf_header) + 1, fp) == NULL)
        return NULL;
    print_elf_header(hdr);
    return hdr;
}

