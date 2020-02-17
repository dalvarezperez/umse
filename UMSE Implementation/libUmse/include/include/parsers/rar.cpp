// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "rar.h"



rar_t::rar_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, rar_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    _read();
}

void rar_t::_read() {
    m_magic = new magic_signature_t(m__io, this, m__root);
    m_blocks = new std::vector<kaitai::kstruct*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            n_blocks = true;
            switch (magic()->version()) {
            case 0: {
                n_blocks = false;
                m_blocks->push_back(new block_t(m__io, this, m__root));
                break;
            }
            case 1: {
                n_blocks = false;
                m_blocks->push_back(new block_v5_t(m__io, this, m__root));
                break;
            }
            }
            i++;
        }
    }
}

rar_t::~rar_t() {
    delete m_magic;
    if (!n_blocks) {
        for (std::vector<kaitai::kstruct*>::iterator it = m_blocks->begin(); it != m_blocks->end(); ++it) {
            delete *it;
        }
        delete m_blocks;
    }
}

rar_t::block_v5_t::block_v5_t(kaitai::kstream* p__io, rar_t* p__parent, rar_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rar_t::block_v5_t::_read() {
}

rar_t::block_v5_t::~block_v5_t() {
}

rar_t::block_t::block_t(kaitai::kstream* p__io, rar_t* p__parent, rar_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_has_add = false;
    f_header_size = false;
    f_body_size = false;
    _read();
}

void rar_t::block_t::_read() {
    m_crc16 = m__io->read_u2le();
    m_block_type = static_cast<rar_t::block_types_t>(m__io->read_u1());
    m_flags = m__io->read_u2le();
    m_block_size = m__io->read_u2le();
    n_add_size = true;
    if (has_add()) {
        n_add_size = false;
        m_add_size = m__io->read_u4le();
    }
    n_body = true;
    switch (block_type()) {
    case BLOCK_TYPES_FILE_HEADER: {
        n_body = false;
        m__raw_body = m__io->read_bytes(body_size());
        m__io__raw_body = new kaitai::kstream(m__raw_body);
        m_body = new block_file_header_t(m__io__raw_body, this, m__root);
        break;
    }
    default: {
        m__raw_body = m__io->read_bytes(body_size());
        break;
    }
    }
    n_add_body = true;
    if (has_add()) {
        n_add_body = false;
        m_add_body = m__io->read_bytes(add_size());
    }
}

rar_t::block_t::~block_t() {
    if (!n_add_size) {
    }
    if (!n_body) {
        delete m__io__raw_body;
        delete m_body;
    }
    if (!n_add_body) {
    }
}

bool rar_t::block_t::has_add() {
    if (f_has_add)
        return m_has_add;
    m_has_add = (flags() & 32768) != 0;
    f_has_add = true;
    return m_has_add;
}

int8_t rar_t::block_t::header_size() {
    if (f_header_size)
        return m_header_size;
    m_header_size = ((has_add()) ? (11) : (7));
    f_header_size = true;
    return m_header_size;
}

int32_t rar_t::block_t::body_size() {
    if (f_body_size)
        return m_body_size;
    m_body_size = (block_size() - header_size());
    f_body_size = true;
    return m_body_size;
}

rar_t::block_file_header_t::block_file_header_t(kaitai::kstream* p__io, rar_t::block_t* p__parent, rar_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rar_t::block_file_header_t::_read() {
    m_low_unp_size = m__io->read_u4le();
    m_host_os = static_cast<rar_t::oses_t>(m__io->read_u1());
    m_file_crc32 = m__io->read_u4le();
    m_file_time = new dos_time_t(m__io, this, m__root);
    m_rar_version = m__io->read_u1();
    m_method = static_cast<rar_t::methods_t>(m__io->read_u1());
    m_name_size = m__io->read_u2le();
    m_attr = m__io->read_u4le();
    n_high_pack_size = true;
    if ((_parent()->flags() & 256) != 0) {
        n_high_pack_size = false;
        m_high_pack_size = m__io->read_u4le();
    }
    m_file_name = m__io->read_bytes(name_size());
    n_salt = true;
    if ((_parent()->flags() & 1024) != 0) {
        n_salt = false;
        m_salt = m__io->read_u8le();
    }
}

rar_t::block_file_header_t::~block_file_header_t() {
    delete m_file_time;
    if (!n_high_pack_size) {
    }
    if (!n_salt) {
    }
}

rar_t::magic_signature_t::magic_signature_t(kaitai::kstream* p__io, rar_t* p__parent, rar_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void rar_t::magic_signature_t::_read() {
    m_magic1 = m__io->ensure_fixed_contents(std::string("\x52\x61\x72\x21\x1A\x07", 6));
    m_version = m__io->read_u1();
    n_magic3 = true;
    if (version() == 1) {
        n_magic3 = false;
        m_magic3 = m__io->ensure_fixed_contents(std::string("\x00", 1));
    }
}

rar_t::magic_signature_t::~magic_signature_t() {
    if (!n_magic3) {
    }
}

rar_t::dos_time_t::dos_time_t(kaitai::kstream* p__io, rar_t::block_file_header_t* p__parent, rar_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_month = false;
    f_seconds = false;
    f_year = false;
    f_minutes = false;
    f_day = false;
    f_hours = false;
    _read();
}

void rar_t::dos_time_t::_read() {
    m_time = m__io->read_u2le();
    m_date = m__io->read_u2le();
}

rar_t::dos_time_t::~dos_time_t() {
}

int32_t rar_t::dos_time_t::month() {
    if (f_month)
        return m_month;
    m_month = ((date() & 480) >> 5);
    f_month = true;
    return m_month;
}

int32_t rar_t::dos_time_t::seconds() {
    if (f_seconds)
        return m_seconds;
    m_seconds = ((time() & 31) * 2);
    f_seconds = true;
    return m_seconds;
}

int32_t rar_t::dos_time_t::year() {
    if (f_year)
        return m_year;
    m_year = (((date() & 65024) >> 9) + 1980);
    f_year = true;
    return m_year;
}

int32_t rar_t::dos_time_t::minutes() {
    if (f_minutes)
        return m_minutes;
    m_minutes = ((time() & 2016) >> 5);
    f_minutes = true;
    return m_minutes;
}

int32_t rar_t::dos_time_t::day() {
    if (f_day)
        return m_day;
    m_day = (date() & 31);
    f_day = true;
    return m_day;
}

int32_t rar_t::dos_time_t::hours() {
    if (f_hours)
        return m_hours;
    m_hours = ((time() & 63488) >> 11);
    f_hours = true;
    return m_hours;
}
