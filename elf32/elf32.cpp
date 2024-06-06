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

#include <cstring>
#include <fcntl.h>
#include <stdexcept>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <elf32/elf32.hpp>

Elf32::Elf32::Elf32(fs::path path) {
    if (!fs::exists(path) || !fs::is_regular_file(path)) {
        throw std::invalid_argument {path.string() + std::string {" does not exist or is not a regular file"}};
    }

    int fd;
    if ((fd = open(path.c_str(), O_RDWR)) == -1) {
        /* throw */
        (void) 0;
    }
    struct stat s;
    if (fstat(fd, &s) == -1) {
        /* throw */
        (void) 0;
    }
    if ((e_header = (Ehdr*)mmap(NULL, s.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        /* throw */
        (void) 0;
    }
    close(fd);

    p_header = (Phdr*)((char*)e_header + e_header->e_phoff);
    s_header = (Shdr*)((char*)e_header + e_header->e_shoff);
    str_tbl = (char *)e_header + s_header[e_header->e_shstrndx].sh_offset;
    size = s.st_size;
}

Elf32::Elf32::~Elf32() {
    msync(e_header, size, MS_SYNC);
    munmap(e_header, size);
}

void Elf32::Elf32::read_section(std::string name, unsigned char* buf, size_t len, off_t offset) {
    for (int i = 0; i < e_header->e_shnum; i++) {
        Shdr* s = &s_header[i];
        if (std::string {&str_tbl[s->sh_name]} == name) {
            memcpy(buf, (unsigned char*)e_header + s->sh_offset + offset, len);
            return;
        }
    }

    /* throw */
}

void Elf32::Elf32::write_section(std::string name, const unsigned char* buf, size_t len, off_t offset) {
    for (int i = 0; i < e_header->e_shnum; i++) {
        Shdr* s = &s_header[i];
        if (std::string {&str_tbl[s->sh_name]} == name) {
            memcpy((unsigned char*)e_header + s->sh_offset + offset, buf, len);
            return;
        }
    }

    /* throw */
}
