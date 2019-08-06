#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "elf.h"
#include "packer.h"
#include "program.h"

static void usage(void)
{
    printf("Usage: ./packer <elf-file> <target-file> <stub-file>\n");
    exit(-1);
}

static void invalid_file(void)
{
    printf("Invalid file, ELF file expected\n");
    exit(-1);
}

FILE *duplicate_file(const char *target_name, elf_header *elf_hdr,
                     program_header **prog_hdrs, FILE *source, char *stub_name)
{
    FILE *targetfp;
    int ch;
    uint32_t i, j, counter = 0;
    // might want to use counter to inject into certain locations
    // TODO make a struct with counter+FILE and just pass that around

    if(!(targetfp = fopen(target_name, "w")))
    {
        printf("Couldn't create target\n");
        exit -1;
    }

    for (i = 0; i < sizeof(elf_header); i++, counter++)
        fputc(((uint8_t *)elf_hdr)[i], targetfp);

    for (j = 0; prog_hdrs[j]; j++)
    {
        for (i = 0; i < sizeof(program_header); i++, counter++)
            fputc(((uint8_t *)prog_hdrs[j])[i], targetfp);

    }

    while ((ch = fgetc(source)) != EOF)
    {
        fputc(ch, targetfp);
        counter++;
    }

    return targetfp;
}

FILE *add_stub(FILE *targetfp, char *stub_name)
{
    FILE *stubfp;
    int ch;

    if ((stubfp = fopen(stub_name, "r")) == NULL)
    {
        printf("Couldn't open stub\n");
        exit -1;
    }
    while ((ch = fgetc(stubfp)) != EOF)
        fputc(ch, targetfp);

    fclose(stubfp);
    return targetfp;
}

int	main(int ac, char **av)
{
    FILE *sourcefp, *targetfp;
    elf_header *elf_hdr;
    program_header **prog_hdrs;

    if (ac < 3)
        usage();

    if ((sourcefp = fopen(av[1], "r+")) == NULL)
        invalid_file();

    if (!(elf_hdr = get_elf_header(sourcefp)))
        invalid_file();

    if (!is_elf(elf_hdr))
        invalid_file();

    printf("Target program header addr: %08lx\n", elf_hdr->e_phoff);
    if (!(prog_hdrs = get_program_headers(sourcefp, elf_hdr->e_phnum)))
        invalid_file();

   /* elf_hdr->e_entry = 0x880; */
    /* prog_hdrs[2]->p_filesz += 0x2f0; */
    /* prog_hdrs[2]->p_memsz += 0x2f0; */

    targetfp = duplicate_file(av[2], elf_hdr, prog_hdrs, sourcefp, av[3]);
    fclose(sourcefp);
    /* targetfp = add_stub(targetfp, av[3]); */

    fclose(targetfp);
    return 0;
}
