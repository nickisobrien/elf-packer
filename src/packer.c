#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "elf.h"
#include "packer.h"
#include "program.h"

static void
usage(void)
{
	printf("Usage: ./packer <elf-file> <stub-file>\n");
	exit(-1);
}

static void
invalid_file(void)
{
	printf("Invalid file, ELF file expected\n");
	exit(-1);
}

FILE *
create_packed_file(elf_header *elf_hdr, program_header **prog_hdrs,
		FILE *source, char *stub_name)
{
	(void)stub_name;
	FILE *targetfp;
	int ch;
	uint32_t i, j, bytes_written = 0;
	/* might want to use bytes_written to inject into certain locations
	 * TODO make a struct with bytes_written+FILE and just pass that around */

	if(!(targetfp = fopen("packed.elf", "w")))
	{
		printf("Couldn't create target\n");
		exit(-1);
	}

	/* write elf header */
	for (i = 0; i < sizeof(elf_header); i++, bytes_written++)
		fputc(((uint8_t *)elf_hdr)[i], targetfp);

	/* write till program_header location
	 * program headers typically follow elf header location
	 * but lets account for the cases where it doesn't */
	while (bytes_written < elf_hdr->e_phoff && (ch = fgetc(source)) != EOF)
	{
		fputc(ch, targetfp);
		bytes_written++;
	}

	/* write program headers */
	for (j = 0; j < elf_hdr->e_phnum; j++)
	{
		for (i = 0; i < sizeof(program_header); i++, bytes_written++)
			fputc( ((uint8_t *) (prog_hdrs[j]))[i] , targetfp);
	}

	/* write the rest of the file */
	while ((ch = fgetc(source)) != EOF)
	{
		fputc(ch, targetfp);
		bytes_written++;
	}
	return targetfp;
}

FILE *
add_stub(FILE *targetfp, char *stub_name)
{
	FILE *stubfp;
	int ch;

	if ((stubfp = fopen(stub_name, "r")) == NULL)
	{
		printf("Couldn't open stub\n");
		exit(-1);
	}
	while ((ch = fgetc(stubfp)) != EOF)
		fputc(ch, targetfp);

	fclose(stubfp);
	return targetfp;
}

int
main(int ac, char **av)
{
	FILE *sourcefp, *targetfp;
	elf_header *elf_hdr;
	program_header **prog_hdrs;

	if (ac < 2)
		usage();

	if (!(sourcefp = fopen(av[1], "r+")))
		invalid_file();

	if (!(elf_hdr = get_elf_header(sourcefp)))
		invalid_file();

	if (!is_elf(elf_hdr))
		invalid_file();

	if (!(prog_hdrs = get_program_headers(sourcefp, elf_hdr->e_phnum)))
		invalid_file();

	targetfp = create_packed_file(elf_hdr, prog_hdrs, sourcefp, av[2]);

	fclose(sourcefp);
	fclose(targetfp);
	return 0;
}
