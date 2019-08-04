#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "elf.h"
#include "packer.h"

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

FILE *duplicate_file(const char *target_name, elf_header *hdr, FILE *source)
{
    FILE *targetfp;
    int ch;
    int i;

    if(!(targetfp = fopen(target_name, "w")))
    {
        printf("Couldn't create target\n");
        exit -1;
    }

    for (i = 0; i < sizeof(elf_header) - 1; i++)
        fputc(((char *)hdr)[i], targetfp);

    while ((ch = fgetc(source)) != EOF)
        fputc(ch, targetfp);

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

    if (ac < 3)
        usage();

    if ((sourcefp = fopen(av[1], "r+")) == NULL)
        invalid_file();

    if (!(elf_hdr = get_elf_header(sourcefp)))
        invalid_file();

    if (!is_elf(elf_hdr))
        invalid_file();

    targetfp = duplicate_file(av[2], elf_hdr, sourcefp);
    fclose(sourcefp);
    targetfp = add_stub(targetfp, av[3]);

    fclose(targetfp);

    return 0;
}
