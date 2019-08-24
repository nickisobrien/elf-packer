#ifndef _SECTION_H_
#define _SECTION_H_

#include <stdint.h>

#if UINTPTR_MAX == 0xffffffff
/* 32-bit */
typedef struct {
    uint32_t   sh_name;
    uint32_t   sh_type;
    uint32_t   sh_flags;
    uint32_t   sh_addr;
    uint32_t   sh_offset;
    uint32_t   sh_size;
    uint32_t   sh_link;
    uint32_t   sh_info;
    uint32_t   sh_addralign;
    uint32_t   sh_entsize;
} section_header;
#elif UINTPTR_MAX == 0xffffffffffffffff
/* 64-bit */
typedef struct {
    uint32_t   sh_name;
    uint32_t   sh_type;
    uint64_t   sh_flags;
    uint64_t   sh_addr;
    uint64_t   sh_offset;
    uint64_t   sh_size;
    uint32_t   sh_link;
    uint32_t   sh_info;
    uint64_t   sh_addralign;
    uint64_t   sh_entsize;
} section_header;
#endif

section_header **get_section_headers(FILE *fp, uint16_t e_phnum);
section_header **add_section_header(FILE *fp);

#endif
