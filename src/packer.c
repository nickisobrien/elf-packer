#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "packer.h"

static void usage(void)
{
    printf("Usage: ./packer <elf-file>\n");
    exit(-1);
}

static void invalid_file(void)
{
    printf("Invalid file, ELF file expected\n");
    exit(-1);
}

static int is_elf(elf_header *hdr)
{
    if (hdr->e_ident[0] != 0x7f)
        return 0;
    if (strncmp((char *)hdr->e_ident+1, ELF_MAG_HEADER, 3))
        return 0;
    return 1;
}

elf_header *read_elf_header(int fd)
{
    elf_header *hdr = (elf_header *)malloc(sizeof(elf_header));
    int read_size = 0;
    if ((read_size = read(fd, hdr, ELF_HDR_SIZE)) < ELF_HDR_SIZE)
        invalid_file();
    return hdr;
}

int	main(int ac, char **av)
{
    int fd;

    if (ac < 2)
        usage();

    if ((fd = open(av[1], O_RDWR)) == -1)
        invalid_file();

    elf_header *elf_hdr = read_elf_header(fd);
    if (!is_elf(elf_hdr))
        invalid_file();

    printf("Program entry point: %llu\n", elf_hdr->e_entry);
    printf("Changing program entry point to %llu\n", 0llu);

    return 0;
}
