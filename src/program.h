#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <stdint.h>

#if UINTPTR_MAX == 0xffffffff
/* 32-bit */
typedef struct __attribute__((packed)) {
	uint32_t   p_type;
	uint32_t   p_offset;
	uint32_t   p_vaddr;
	uint32_t   p_paddr;
	uint32_t   p_filesz;
	uint32_t   p_memsz;
	uint32_t   p_flags;
	uint32_t   p_align;
} program_header;

#elif UINTPTR_MAX == 0xffffffffffffffff
/* 64-bit */
typedef struct __attribute__((packed)) {
	uint32_t   p_type;
	uint32_t   p_flags;
	uint64_t   p_offset;
	uint64_t   p_vaddr;
	uint64_t   p_paddr;
	uint64_t   p_filesz;
	uint64_t   p_memsz;
	uint64_t   p_align;
} program_header;
#endif

program_header **get_program_headers(FILE *fp, uint16_t e_phnum);
program_header **add_program_header(FILE *fp);

#endif
