// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "dos_mz.h"



dos_mz_t::dos_mz_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, dos_mz_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    _read();
}

void dos_mz_t::_read() {
    m_hdr = new mz_header_t(m__io, this, m__root);
    m_mz_header2 = m__io->read_bytes((hdr()->relocations_ofs() - 28));
    int l_relocations = hdr()->qty_relocations();
    m_relocations = new std::vector<relocation_t*>();
    m_relocations->reserve(l_relocations);
    for (int i = 0; i < l_relocations; i++) {
        m_relocations->push_back(new relocation_t(m__io, this, m__root));
    }
    m_body = m__io->read_bytes_full();
}

dos_mz_t::~dos_mz_t() {
    delete m_hdr;
    for (std::vector<relocation_t*>::iterator it = m_relocations->begin(); it != m_relocations->end(); ++it) {
        delete *it;
    }
    delete m_relocations;
}

dos_mz_t::mz_header_t::mz_header_t(kaitai::kstream* p__io, dos_mz_t* p__parent, dos_mz_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void dos_mz_t::mz_header_t::_read() {
    m_magic = m__io->read_bytes(2);
    m_last_page_extra_bytes = m__io->read_u2le();
    m_qty_pages = m__io->read_u2le();
    m_qty_relocations = m__io->read_u2le();
    m_header_size = m__io->read_u2le();
    m_min_allocation = m__io->read_u2le();
    m_max_allocation = m__io->read_u2le();
    m_initial_ss = m__io->read_u2le();
    m_initial_sp = m__io->read_u2le();
    m_checksum = m__io->read_u2le();
    m_initial_ip = m__io->read_u2le();
    m_initial_cs = m__io->read_u2le();
    m_relocations_ofs = m__io->read_u2le();
    m_overlay_id = m__io->read_u2le();
}

dos_mz_t::mz_header_t::~mz_header_t() {
}

dos_mz_t::relocation_t::relocation_t(kaitai::kstream* p__io, dos_mz_t* p__parent, dos_mz_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void dos_mz_t::relocation_t::_read() {
    m_ofs = m__io->read_u2le();
    m_seg = m__io->read_u2le();
}

dos_mz_t::relocation_t::~relocation_t() {
}
