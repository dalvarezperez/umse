// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "elf.h"

#include <stdexcept>

elf_t::elf_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, elf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    _read();
}

void elf_t::_read() {
    m_magic = m__io->ensure_fixed_contents(std::string("\x7F\x45\x4C\x46", 4));
    m_bits = static_cast<elf_t::bits_t>(m__io->read_u1());
    m_endian = static_cast<elf_t::endian_t>(m__io->read_u1());
    m_ei_version = m__io->read_u1();
    m_abi = static_cast<elf_t::os_abi_t>(m__io->read_u1());
    m_abi_version = m__io->read_u1();
    m_pad = m__io->read_bytes(7);
    m_header = new endian_elf_t(m__io, this, m__root);
}

elf_t::~elf_t() {
    delete m_header;
}

elf_t::endian_elf_t::endian_elf_t(kaitai::kstream* p__io, elf_t* p__parent, elf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m__is_le = -1;
    f_program_headers = false;
    f_section_headers = false;
    f_strings = false;
    _read();
}

void elf_t::endian_elf_t::_read() {
    switch (_root()->endian()) {
    case ENDIAN_LE: {
        m__is_le = true;
        break;
    }
    case ENDIAN_BE: {
        m__is_le = false;
        break;
    }
    }

    if (m__is_le == -1) {
        throw std::runtime_error("unable to decide on endianness");
    } else if (m__is_le == 1) {
        _read_le();
    } else {
        _read_be();
    }
}

void elf_t::endian_elf_t::_read_le() {
    m_e_type = static_cast<elf_t::obj_type_t>(m__io->read_u2le());
    m_machine = static_cast<elf_t::machine_t>(m__io->read_u2le());
    m_e_version = m__io->read_u4le();
    n_entry_point = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_entry_point = false;
        m_entry_point = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_entry_point = false;
        m_entry_point = m__io->read_u8le();
        break;
    }
    }
    n_program_header_offset = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_program_header_offset = false;
        m_program_header_offset = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_program_header_offset = false;
        m_program_header_offset = m__io->read_u8le();
        break;
    }
    }
    n_section_header_offset = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_section_header_offset = false;
        m_section_header_offset = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_section_header_offset = false;
        m_section_header_offset = m__io->read_u8le();
        break;
    }
    }
    m_flags = m__io->read_bytes(4);
    m_e_ehsize = m__io->read_u2le();
    m_program_header_entry_size = m__io->read_u2le();
    m_qty_program_header = m__io->read_u2le();
    m_section_header_entry_size = m__io->read_u2le();
    m_qty_section_header = m__io->read_u2le();
    m_section_names_idx = m__io->read_u2le();
}

void elf_t::endian_elf_t::_read_be() {
    m_e_type = static_cast<elf_t::obj_type_t>(m__io->read_u2be());
    m_machine = static_cast<elf_t::machine_t>(m__io->read_u2be());
    m_e_version = m__io->read_u4be();
    n_entry_point = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_entry_point = false;
        m_entry_point = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_entry_point = false;
        m_entry_point = m__io->read_u8be();
        break;
    }
    }
    n_program_header_offset = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_program_header_offset = false;
        m_program_header_offset = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_program_header_offset = false;
        m_program_header_offset = m__io->read_u8be();
        break;
    }
    }
    n_section_header_offset = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_section_header_offset = false;
        m_section_header_offset = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_section_header_offset = false;
        m_section_header_offset = m__io->read_u8be();
        break;
    }
    }
    m_flags = m__io->read_bytes(4);
    m_e_ehsize = m__io->read_u2be();
    m_program_header_entry_size = m__io->read_u2be();
    m_qty_program_header = m__io->read_u2be();
    m_section_header_entry_size = m__io->read_u2be();
    m_qty_section_header = m__io->read_u2be();
    m_section_names_idx = m__io->read_u2be();
}

elf_t::endian_elf_t::~endian_elf_t() {
    if (!n_entry_point) {
    }
    if (!n_program_header_offset) {
    }
    if (!n_section_header_offset) {
    }
    if (f_program_headers) {
        delete m__raw_program_headers;
        for (std::vector<kaitai::kstream*>::iterator it = m__io__raw_program_headers->begin(); it != m__io__raw_program_headers->end(); ++it) {
            delete *it;
        }
        delete m__io__raw_program_headers;
        for (std::vector<program_header_t*>::iterator it = m_program_headers->begin(); it != m_program_headers->end(); ++it) {
            delete *it;
        }
        delete m_program_headers;
    }
    if (f_section_headers) {
        delete m__raw_section_headers;
        for (std::vector<kaitai::kstream*>::iterator it = m__io__raw_section_headers->begin(); it != m__io__raw_section_headers->end(); ++it) {
            delete *it;
        }
        delete m__io__raw_section_headers;
        for (std::vector<section_header_t*>::iterator it = m_section_headers->begin(); it != m_section_headers->end(); ++it) {
            delete *it;
        }
        delete m_section_headers;
    }
    if (f_strings) {
        delete m__io__raw_strings;
        delete m_strings;
    }
}

elf_t::endian_elf_t::program_header_t::program_header_t(kaitai::kstream* p__io, elf_t::endian_elf_t* p__parent, elf_t* p__root, int p_is_le) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m__is_le = p_is_le;
    _read();
}

void elf_t::endian_elf_t::program_header_t::_read() {

    if (m__is_le == -1) {
        throw std::runtime_error("unable to decide on endianness");
    } else if (m__is_le == 1) {
        _read_le();
    } else {
        _read_be();
    }
}

void elf_t::endian_elf_t::program_header_t::_read_le() {
    m_type = static_cast<elf_t::ph_type_t>(m__io->read_u4le());
    n_flags64 = true;
    if (_root()->bits() == BITS_B64) {
        n_flags64 = false;
        m_flags64 = m__io->read_u4le();
    }
    n_offset = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_offset = false;
        m_offset = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_offset = false;
        m_offset = m__io->read_u8le();
        break;
    }
    }
    n_vaddr = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_vaddr = false;
        m_vaddr = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_vaddr = false;
        m_vaddr = m__io->read_u8le();
        break;
    }
    }
    n_paddr = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_paddr = false;
        m_paddr = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_paddr = false;
        m_paddr = m__io->read_u8le();
        break;
    }
    }
    n_filesz = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_filesz = false;
        m_filesz = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_filesz = false;
        m_filesz = m__io->read_u8le();
        break;
    }
    }
    n_memsz = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_memsz = false;
        m_memsz = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_memsz = false;
        m_memsz = m__io->read_u8le();
        break;
    }
    }
    n_flags32 = true;
    if (_root()->bits() == BITS_B32) {
        n_flags32 = false;
        m_flags32 = m__io->read_u4le();
    }
    n_align = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_align = false;
        m_align = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_align = false;
        m_align = m__io->read_u8le();
        break;
    }
    }
}

void elf_t::endian_elf_t::program_header_t::_read_be() {
    m_type = static_cast<elf_t::ph_type_t>(m__io->read_u4be());
    n_flags64 = true;
    if (_root()->bits() == BITS_B64) {
        n_flags64 = false;
        m_flags64 = m__io->read_u4be();
    }
    n_offset = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_offset = false;
        m_offset = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_offset = false;
        m_offset = m__io->read_u8be();
        break;
    }
    }
    n_vaddr = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_vaddr = false;
        m_vaddr = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_vaddr = false;
        m_vaddr = m__io->read_u8be();
        break;
    }
    }
    n_paddr = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_paddr = false;
        m_paddr = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_paddr = false;
        m_paddr = m__io->read_u8be();
        break;
    }
    }
    n_filesz = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_filesz = false;
        m_filesz = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_filesz = false;
        m_filesz = m__io->read_u8be();
        break;
    }
    }
    n_memsz = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_memsz = false;
        m_memsz = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_memsz = false;
        m_memsz = m__io->read_u8be();
        break;
    }
    }
    n_flags32 = true;
    if (_root()->bits() == BITS_B32) {
        n_flags32 = false;
        m_flags32 = m__io->read_u4be();
    }
    n_align = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_align = false;
        m_align = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_align = false;
        m_align = m__io->read_u8be();
        break;
    }
    }
}

elf_t::endian_elf_t::program_header_t::~program_header_t() {
    if (!n_flags64) {
    }
    if (!n_offset) {
    }
    if (!n_vaddr) {
    }
    if (!n_paddr) {
    }
    if (!n_filesz) {
    }
    if (!n_memsz) {
    }
    if (!n_flags32) {
    }
    if (!n_align) {
    }
}

elf_t::endian_elf_t::section_header_t::section_header_t(kaitai::kstream* p__io, elf_t::endian_elf_t* p__parent, elf_t* p__root, int p_is_le) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m__is_le = p_is_le;
    f_body = false;
    f_name = false;
    _read();
}

void elf_t::endian_elf_t::section_header_t::_read() {

    if (m__is_le == -1) {
        throw std::runtime_error("unable to decide on endianness");
    } else if (m__is_le == 1) {
        _read_le();
    } else {
        _read_be();
    }
}

void elf_t::endian_elf_t::section_header_t::_read_le() {
    m_name_offset = m__io->read_u4le();
    m_type = static_cast<elf_t::sh_type_t>(m__io->read_u4le());
    n_flags = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_flags = false;
        m_flags = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_flags = false;
        m_flags = m__io->read_u8le();
        break;
    }
    }
    n_addr = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_addr = false;
        m_addr = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_addr = false;
        m_addr = m__io->read_u8le();
        break;
    }
    }
    n_offset = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_offset = false;
        m_offset = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_offset = false;
        m_offset = m__io->read_u8le();
        break;
    }
    }
    n_size = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_size = false;
        m_size = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_size = false;
        m_size = m__io->read_u8le();
        break;
    }
    }
    m_linked_section_idx = m__io->read_u4le();
    m_info = m__io->read_bytes(4);
    n_align = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_align = false;
        m_align = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_align = false;
        m_align = m__io->read_u8le();
        break;
    }
    }
    n_entry_size = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_entry_size = false;
        m_entry_size = m__io->read_u4le();
        break;
    }
    case BITS_B64: {
        n_entry_size = false;
        m_entry_size = m__io->read_u8le();
        break;
    }
    }
}

void elf_t::endian_elf_t::section_header_t::_read_be() {
    m_name_offset = m__io->read_u4be();
    m_type = static_cast<elf_t::sh_type_t>(m__io->read_u4be());
    n_flags = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_flags = false;
        m_flags = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_flags = false;
        m_flags = m__io->read_u8be();
        break;
    }
    }
    n_addr = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_addr = false;
        m_addr = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_addr = false;
        m_addr = m__io->read_u8be();
        break;
    }
    }
    n_offset = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_offset = false;
        m_offset = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_offset = false;
        m_offset = m__io->read_u8be();
        break;
    }
    }
    n_size = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_size = false;
        m_size = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_size = false;
        m_size = m__io->read_u8be();
        break;
    }
    }
    m_linked_section_idx = m__io->read_u4be();
    m_info = m__io->read_bytes(4);
    n_align = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_align = false;
        m_align = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_align = false;
        m_align = m__io->read_u8be();
        break;
    }
    }
    n_entry_size = true;
    switch (_root()->bits()) {
    case BITS_B32: {
        n_entry_size = false;
        m_entry_size = m__io->read_u4be();
        break;
    }
    case BITS_B64: {
        n_entry_size = false;
        m_entry_size = m__io->read_u8be();
        break;
    }
    }
}

elf_t::endian_elf_t::section_header_t::~section_header_t() {
    if (!n_flags) {
    }
    if (!n_addr) {
    }
    if (!n_offset) {
    }
    if (!n_size) {
    }
    if (!n_align) {
    }
    if (!n_entry_size) {
    }
    if (f_body) {
    }
    if (f_name) {
    }
}

std::string elf_t::endian_elf_t::section_header_t::body() {
    if (f_body)
        return m_body;
    kaitai::kstream *io = _root()->_io();
    std::streampos _pos = io->pos();
    io->seek(offset());
    if (m__is_le == 1) {
        m_body = io->read_bytes(size());
    } else {
        m_body = io->read_bytes(size());
    }
    io->seek(_pos);
    f_body = true;
    return m_body;
}

std::string elf_t::endian_elf_t::section_header_t::name() {
    if (f_name)
        return m_name;
    kaitai::kstream *io = _root()->header()->strings()->_io();
    std::streampos _pos = io->pos();
    io->seek(name_offset());
    if (m__is_le == 1) {
        m_name = kaitai::kstream::bytes_to_str(io->read_bytes_term(0, false, true, true), std::string("ASCII"));
    } else {
        m_name = kaitai::kstream::bytes_to_str(io->read_bytes_term(0, false, true, true), std::string("ASCII"));
    }
    io->seek(_pos);
    f_name = true;
    return m_name;
}

elf_t::endian_elf_t::strings_struct_t::strings_struct_t(kaitai::kstream* p__io, elf_t::endian_elf_t* p__parent, elf_t* p__root, int p_is_le) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m__is_le = p_is_le;
    _read();
}

void elf_t::endian_elf_t::strings_struct_t::_read() {

    if (m__is_le == -1) {
        throw std::runtime_error("unable to decide on endianness");
    } else if (m__is_le == 1) {
        _read_le();
    } else {
        _read_be();
    }
}

void elf_t::endian_elf_t::strings_struct_t::_read_le() {
    m_entries = new std::vector<std::string>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_entries->push_back(kaitai::kstream::bytes_to_str(m__io->read_bytes_term(0, false, true, true), std::string("ASCII")));
            i++;
        }
    }
}

void elf_t::endian_elf_t::strings_struct_t::_read_be() {
    m_entries = new std::vector<std::string>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_entries->push_back(kaitai::kstream::bytes_to_str(m__io->read_bytes_term(0, false, true, true), std::string("ASCII")));
            i++;
        }
    }
}

elf_t::endian_elf_t::strings_struct_t::~strings_struct_t() {
    delete m_entries;
}

std::vector<elf_t::endian_elf_t::program_header_t*>* elf_t::endian_elf_t::program_headers() {
    if (f_program_headers)
        return m_program_headers;
    std::streampos _pos = m__io->pos();
    m__io->seek(program_header_offset());
    if (m__is_le == 1) {
        int l_program_headers = qty_program_header();
        m__raw_program_headers = new std::vector<std::string>();
        m__raw_program_headers->reserve(l_program_headers);
        m__io__raw_program_headers = new std::vector<kaitai::kstream*>();
        m__io__raw_program_headers->reserve(l_program_headers);
        m_program_headers = new std::vector<program_header_t*>();
        m_program_headers->reserve(l_program_headers);
        for (int i = 0; i < l_program_headers; i++) {
            m__raw_program_headers->push_back(m__io->read_bytes(program_header_entry_size()));
            kaitai::kstream* io__raw_program_headers = new kaitai::kstream(m__raw_program_headers->at(m__raw_program_headers->size() - 1));
            m__io__raw_program_headers->push_back(io__raw_program_headers);
            m_program_headers->push_back(new program_header_t(io__raw_program_headers, this, m__root, m__is_le));
        }
    } else {
        int l_program_headers = qty_program_header();
        m__raw_program_headers = new std::vector<std::string>();
        m__raw_program_headers->reserve(l_program_headers);
        m__io__raw_program_headers = new std::vector<kaitai::kstream*>();
        m__io__raw_program_headers->reserve(l_program_headers);
        m_program_headers = new std::vector<program_header_t*>();
        m_program_headers->reserve(l_program_headers);
        for (int i = 0; i < l_program_headers; i++) {
            m__raw_program_headers->push_back(m__io->read_bytes(program_header_entry_size()));
            kaitai::kstream* io__raw_program_headers = new kaitai::kstream(m__raw_program_headers->at(m__raw_program_headers->size() - 1));
            m__io__raw_program_headers->push_back(io__raw_program_headers);
            m_program_headers->push_back(new program_header_t(io__raw_program_headers, this, m__root, m__is_le));
        }
    }
    m__io->seek(_pos);
    f_program_headers = true;
    return m_program_headers;
}

std::vector<elf_t::endian_elf_t::section_header_t*>* elf_t::endian_elf_t::section_headers() {
    if (f_section_headers)
        return m_section_headers;
    std::streampos _pos = m__io->pos();
    m__io->seek(section_header_offset());
    if (m__is_le == 1) {
        int l_section_headers = qty_section_header();
        m__raw_section_headers = new std::vector<std::string>();
        m__raw_section_headers->reserve(l_section_headers);
        m__io__raw_section_headers = new std::vector<kaitai::kstream*>();
        m__io__raw_section_headers->reserve(l_section_headers);
        m_section_headers = new std::vector<section_header_t*>();
        m_section_headers->reserve(l_section_headers);
        for (int i = 0; i < l_section_headers; i++) {
            m__raw_section_headers->push_back(m__io->read_bytes(section_header_entry_size()));
            kaitai::kstream* io__raw_section_headers = new kaitai::kstream(m__raw_section_headers->at(m__raw_section_headers->size() - 1));
            m__io__raw_section_headers->push_back(io__raw_section_headers);
            m_section_headers->push_back(new section_header_t(io__raw_section_headers, this, m__root, m__is_le));
        }
    } else {
        int l_section_headers = qty_section_header();
        m__raw_section_headers = new std::vector<std::string>();
        m__raw_section_headers->reserve(l_section_headers);
        m__io__raw_section_headers = new std::vector<kaitai::kstream*>();
        m__io__raw_section_headers->reserve(l_section_headers);
        m_section_headers = new std::vector<section_header_t*>();
        m_section_headers->reserve(l_section_headers);
        for (int i = 0; i < l_section_headers; i++) {
            m__raw_section_headers->push_back(m__io->read_bytes(section_header_entry_size()));
            kaitai::kstream* io__raw_section_headers = new kaitai::kstream(m__raw_section_headers->at(m__raw_section_headers->size() - 1));
            m__io__raw_section_headers->push_back(io__raw_section_headers);
            m_section_headers->push_back(new section_header_t(io__raw_section_headers, this, m__root, m__is_le));
        }
    }
    m__io->seek(_pos);
    f_section_headers = true;
    return m_section_headers;
}

elf_t::endian_elf_t::strings_struct_t* elf_t::endian_elf_t::strings() {
    if (f_strings)
        return m_strings;
    std::streampos _pos = m__io->pos();
    m__io->seek(section_headers()->at(section_names_idx())->offset());
    if (m__is_le == 1) {
        m__raw_strings = m__io->read_bytes(section_headers()->at(section_names_idx())->size());
        m__io__raw_strings = new kaitai::kstream(m__raw_strings);
        m_strings = new strings_struct_t(m__io__raw_strings, this, m__root, m__is_le);
    } else {
        m__raw_strings = m__io->read_bytes(section_headers()->at(section_names_idx())->size());
        m__io__raw_strings = new kaitai::kstream(m__raw_strings);
        m_strings = new strings_struct_t(m__io__raw_strings, this, m__root, m__is_le);
    }
    m__io->seek(_pos);
    f_strings = true;
    return m_strings;
}
