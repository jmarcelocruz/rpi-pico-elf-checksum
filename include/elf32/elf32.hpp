/* Copyright 2024 José Marcelo Marques da Cruz
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdint>

#define EI_NIDENT (16)

namespace Elf32 {
    using Addr_t = uint32_t;
    using Half_t = uint16_t;
    using Off_t = uint32_t;
    using Sword_t = int32_t;
    using Word_t = uint32_t;

    struct Ehdr {
        unsigned char e_ident[EI_NIDENT];
        Half_t e_type;
        Half_t e_machine;
        Word_t e_version;
        Addr_t e_entry;
        Off_t e_phoff;
        Off_t e_shoff;
        Word_t e_flags;
        Half_t e_ehsize;
        Half_t e_phentsize;
        Half_t e_phnum;
        Half_t e_shentsize;
        Half_t e_shnum;
        Half_t e_shstrndx;
    };

    struct Phdr {
        Word_t p_type;
        Off_t p_offset;
        Addr_t p_vaddr;
        Addr_t p_paddr;
        Word_t p_filesz;
        Word_t p_memsz;
        Word_t p_flags;
        Word_t p_align;
    };

    struct Shdr {
        Word_t sh_name;
        Word_t sh_type;
        Word_t sh_flags;
        Addr_t sh_addr;
        Off_t sh_offset;
        Word_t sh_size;
        Word_t sh_link;
        Word_t sh_info;
        Word_t sh_addralign;
        Word_t sh_entsize;
    };
}
