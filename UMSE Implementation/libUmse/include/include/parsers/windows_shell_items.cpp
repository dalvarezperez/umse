// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "windows_shell_items.h"



windows_shell_items_t::windows_shell_items_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, windows_shell_items_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    _read();
}

void windows_shell_items_t::_read() {
    m_items = new std::vector<shell_item_t*>();
    {
        int i = 0;
        shell_item_t* _;
        do {
            _ = new shell_item_t(m__io, this, m__root);
            m_items->push_back(_);
            i++;
        } while (!(_->len_data() == 0));
    }
}

windows_shell_items_t::~windows_shell_items_t() {
    for (std::vector<shell_item_t*>::iterator it = m_items->begin(); it != m_items->end(); ++it) {
        delete *it;
    }
    delete m_items;
}

windows_shell_items_t::shell_item_data_t::shell_item_data_t(kaitai::kstream* p__io, windows_shell_items_t::shell_item_t* p__parent, windows_shell_items_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void windows_shell_items_t::shell_item_data_t::_read() {
    m_code = m__io->read_u1();
    n_body1 = true;
    switch (code()) {
    case 31: {
        n_body1 = false;
        m_body1 = new root_folder_body_t(m__io, this, m__root);
        break;
    }
    }
    n_body2 = true;
    switch ((code() & 112)) {
    case 32: {
        n_body2 = false;
        m_body2 = new volume_body_t(m__io, this, m__root);
        break;
    }
    case 48: {
        n_body2 = false;
        m_body2 = new file_entry_body_t(m__io, this, m__root);
        break;
    }
    }
}

windows_shell_items_t::shell_item_data_t::~shell_item_data_t() {
    if (!n_body1) {
        delete m_body1;
    }
    if (!n_body2) {
        delete m_body2;
    }
}

windows_shell_items_t::shell_item_t::shell_item_t(kaitai::kstream* p__io, windows_shell_items_t* p__parent, windows_shell_items_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void windows_shell_items_t::shell_item_t::_read() {
    m_len_data = m__io->read_u2le();
    n_data = true;
    if (len_data() >= 2) {
        n_data = false;
        m__raw_data = m__io->read_bytes((len_data() - 2));
        m__io__raw_data = new kaitai::kstream(m__raw_data);
        m_data = new shell_item_data_t(m__io__raw_data, this, m__root);
    }
}

windows_shell_items_t::shell_item_t::~shell_item_t() {
    if (!n_data) {
        delete m__io__raw_data;
        delete m_data;
    }
}

windows_shell_items_t::root_folder_body_t::root_folder_body_t(kaitai::kstream* p__io, windows_shell_items_t::shell_item_data_t* p__parent, windows_shell_items_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void windows_shell_items_t::root_folder_body_t::_read() {
    m_sort_index = m__io->read_u1();
    m_shell_folder_id = m__io->read_bytes(16);
}

windows_shell_items_t::root_folder_body_t::~root_folder_body_t() {
}

windows_shell_items_t::volume_body_t::volume_body_t(kaitai::kstream* p__io, windows_shell_items_t::shell_item_data_t* p__parent, windows_shell_items_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void windows_shell_items_t::volume_body_t::_read() {
    m_flags = m__io->read_u1();
}

windows_shell_items_t::volume_body_t::~volume_body_t() {
}

windows_shell_items_t::file_entry_body_t::file_entry_body_t(kaitai::kstream* p__io, windows_shell_items_t::shell_item_data_t* p__parent, windows_shell_items_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_is_dir = false;
    f_is_file = false;
    _read();
}

void windows_shell_items_t::file_entry_body_t::_read() {
    m__unnamed0 = m__io->read_u1();
    m_file_size = m__io->read_u4le();
    m_last_mod_time = m__io->read_u4le();
    m_file_attrs = m__io->read_u2le();
}

windows_shell_items_t::file_entry_body_t::~file_entry_body_t() {
}

bool windows_shell_items_t::file_entry_body_t::is_dir() {
    if (f_is_dir)
        return m_is_dir;
    m_is_dir = (_parent()->code() & 1) != 0;
    f_is_dir = true;
    return m_is_dir;
}

bool windows_shell_items_t::file_entry_body_t::is_file() {
    if (f_is_file)
        return m_is_file;
    m_is_file = (_parent()->code() & 2) != 0;
    f_is_file = true;
    return m_is_file;
}
