// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "regf.h"



regf_t::regf_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    _read();
}

void regf_t::_read() {
    m_header = new file_header_t(m__io, this, m__root);
    m__raw_hive_bins = new std::vector<std::string>();
    m__io__raw_hive_bins = new std::vector<kaitai::kstream*>();
    m_hive_bins = new std::vector<hive_bin_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m__raw_hive_bins->push_back(m__io->read_bytes(4096));
            kaitai::kstream* io__raw_hive_bins = new kaitai::kstream(m__raw_hive_bins->at(m__raw_hive_bins->size() - 1));
            m__io__raw_hive_bins->push_back(io__raw_hive_bins);
            m_hive_bins->push_back(new hive_bin_t(io__raw_hive_bins, this, m__root));
            i++;
        }
    }
}

regf_t::~regf_t() {
    delete m_header;
    delete m__raw_hive_bins;
    for (std::vector<kaitai::kstream*>::iterator it = m__io__raw_hive_bins->begin(); it != m__io__raw_hive_bins->end(); ++it) {
        delete *it;
    }
    delete m__io__raw_hive_bins;
    for (std::vector<hive_bin_t*>::iterator it = m_hive_bins->begin(); it != m_hive_bins->end(); ++it) {
        delete *it;
    }
    delete m_hive_bins;
}

regf_t::filetime_t::filetime_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void regf_t::filetime_t::_read() {
    m_value = m__io->read_u8le();
}

regf_t::filetime_t::~filetime_t() {
}

regf_t::hive_bin_t::hive_bin_t(kaitai::kstream* p__io, regf_t* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void regf_t::hive_bin_t::_read() {
    m_header = new hive_bin_header_t(m__io, this, m__root);
    m_cells = new std::vector<hive_bin_cell_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_cells->push_back(new hive_bin_cell_t(m__io, this, m__root));
            i++;
        }
    }
}

regf_t::hive_bin_t::~hive_bin_t() {
    delete m_header;
    for (std::vector<hive_bin_cell_t*>::iterator it = m_cells->begin(); it != m_cells->end(); ++it) {
        delete *it;
    }
    delete m_cells;
}

regf_t::hive_bin_header_t::hive_bin_header_t(kaitai::kstream* p__io, regf_t::hive_bin_t* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void regf_t::hive_bin_header_t::_read() {
    m_signature = m__io->ensure_fixed_contents(std::string("\x68\x62\x69\x6E", 4));
    m_offset = m__io->read_u4le();
    m_size = m__io->read_u4le();
    m_unknown1 = m__io->read_u4le();
    m_unknown2 = m__io->read_u4le();
    m_timestamp = new filetime_t(m__io, this, m__root);
    m_unknown4 = m__io->read_u4le();
}

regf_t::hive_bin_header_t::~hive_bin_header_t() {
    delete m_timestamp;
}

regf_t::hive_bin_cell_t::hive_bin_cell_t(kaitai::kstream* p__io, regf_t::hive_bin_t* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_cell_size = false;
    f_is_allocated = false;
    _read();
}

void regf_t::hive_bin_cell_t::_read() {
    m_cell_size_raw = m__io->read_s4le();
    m_identifier = kaitai::kstream::bytes_to_str(m__io->read_bytes(2), std::string("ascii"));
    n_data = true;
    {
        std::string on = identifier();
        if (on == std::string("li")) {
            n_data = false;
            m__raw_data = m__io->read_bytes(((cell_size() - 2) - 4));
            m__io__raw_data = new kaitai::kstream(m__raw_data);
            m_data = new sub_key_list_li_t(m__io__raw_data, this, m__root);
        }
        else if (on == std::string("vk")) {
            n_data = false;
            m__raw_data = m__io->read_bytes(((cell_size() - 2) - 4));
            m__io__raw_data = new kaitai::kstream(m__raw_data);
            m_data = new sub_key_list_vk_t(m__io__raw_data, this, m__root);
        }
        else if (on == std::string("lf")) {
            n_data = false;
            m__raw_data = m__io->read_bytes(((cell_size() - 2) - 4));
            m__io__raw_data = new kaitai::kstream(m__raw_data);
            m_data = new sub_key_list_lh_lf_t(m__io__raw_data, this, m__root);
        }
        else if (on == std::string("ri")) {
            n_data = false;
            m__raw_data = m__io->read_bytes(((cell_size() - 2) - 4));
            m__io__raw_data = new kaitai::kstream(m__raw_data);
            m_data = new sub_key_list_ri_t(m__io__raw_data, this, m__root);
        }
        else if (on == std::string("lh")) {
            n_data = false;
            m__raw_data = m__io->read_bytes(((cell_size() - 2) - 4));
            m__io__raw_data = new kaitai::kstream(m__raw_data);
            m_data = new sub_key_list_lh_lf_t(m__io__raw_data, this, m__root);
        }
        else if (on == std::string("nk")) {
            n_data = false;
            m__raw_data = m__io->read_bytes(((cell_size() - 2) - 4));
            m__io__raw_data = new kaitai::kstream(m__raw_data);
            m_data = new named_key_t(m__io__raw_data, this, m__root);
        }
        else if (on == std::string("sk")) {
            n_data = false;
            m__raw_data = m__io->read_bytes(((cell_size() - 2) - 4));
            m__io__raw_data = new kaitai::kstream(m__raw_data);
            m_data = new sub_key_list_sk_t(m__io__raw_data, this, m__root);
        }
        else {
            m__raw_data = m__io->read_bytes(((cell_size() - 2) - 4));
        }
    }
}

regf_t::hive_bin_cell_t::~hive_bin_cell_t() {
    if (!n_data) {
        delete m__io__raw_data;
        delete m_data;
    }
}

regf_t::hive_bin_cell_t::sub_key_list_vk_t::sub_key_list_vk_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void regf_t::hive_bin_cell_t::sub_key_list_vk_t::_read() {
    m_value_name_size = m__io->read_u2le();
    m_data_size = m__io->read_u4le();
    m_data_offset = m__io->read_u4le();
    m_data_type = static_cast<regf_t::hive_bin_cell_t::sub_key_list_vk_t::data_type_enum_t>(m__io->read_u4le());
    m_flags = static_cast<regf_t::hive_bin_cell_t::sub_key_list_vk_t::vk_flags_t>(m__io->read_u2le());
    m_padding = m__io->read_u2le();
    n_value_name = true;
    if (flags() == VK_FLAGS_VALUE_COMP_NAME) {
        n_value_name = false;
        m_value_name = kaitai::kstream::bytes_to_str(m__io->read_bytes(value_name_size()), std::string("ascii"));
    }
}

regf_t::hive_bin_cell_t::sub_key_list_vk_t::~sub_key_list_vk_t() {
    if (!n_value_name) {
    }
}

regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t::sub_key_list_lh_lf_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t::_read() {
    m_count = m__io->read_u2le();
    int l_items = count();
    m_items = new std::vector<item_t*>();
    m_items->reserve(l_items);
    for (int i = 0; i < l_items; i++) {
        m_items->push_back(new item_t(m__io, this, m__root));
    }
}

regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t::~sub_key_list_lh_lf_t() {
    for (std::vector<item_t*>::iterator it = m_items->begin(); it != m_items->end(); ++it) {
        delete *it;
    }
    delete m_items;
}

regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t::item_t::item_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t::item_t::_read() {
    m_named_key_offset = m__io->read_u4le();
    m_hash_value = m__io->read_u4le();
}

regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t::item_t::~item_t() {
}

regf_t::hive_bin_cell_t::sub_key_list_sk_t::sub_key_list_sk_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void regf_t::hive_bin_cell_t::sub_key_list_sk_t::_read() {
    m_unknown1 = m__io->read_u2le();
    m_previous_security_key_offset = m__io->read_u4le();
    m_next_security_key_offset = m__io->read_u4le();
    m_reference_count = m__io->read_u4le();
}

regf_t::hive_bin_cell_t::sub_key_list_sk_t::~sub_key_list_sk_t() {
}

regf_t::hive_bin_cell_t::sub_key_list_li_t::sub_key_list_li_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void regf_t::hive_bin_cell_t::sub_key_list_li_t::_read() {
    m_count = m__io->read_u2le();
    int l_items = count();
    m_items = new std::vector<item_t*>();
    m_items->reserve(l_items);
    for (int i = 0; i < l_items; i++) {
        m_items->push_back(new item_t(m__io, this, m__root));
    }
}

regf_t::hive_bin_cell_t::sub_key_list_li_t::~sub_key_list_li_t() {
    for (std::vector<item_t*>::iterator it = m_items->begin(); it != m_items->end(); ++it) {
        delete *it;
    }
    delete m_items;
}

regf_t::hive_bin_cell_t::sub_key_list_li_t::item_t::item_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t::sub_key_list_li_t* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void regf_t::hive_bin_cell_t::sub_key_list_li_t::item_t::_read() {
    m_named_key_offset = m__io->read_u4le();
}

regf_t::hive_bin_cell_t::sub_key_list_li_t::item_t::~item_t() {
}

regf_t::hive_bin_cell_t::named_key_t::named_key_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void regf_t::hive_bin_cell_t::named_key_t::_read() {
    m_flags = static_cast<regf_t::hive_bin_cell_t::named_key_t::nk_flags_t>(m__io->read_u2le());
    m_last_key_written_date_and_time = new filetime_t(m__io, this, m__root);
    m_unknown1 = m__io->read_u4le();
    m_parent_key_offset = m__io->read_u4le();
    m_number_of_sub_keys = m__io->read_u4le();
    m_number_of_volatile_sub_keys = m__io->read_u4le();
    m_sub_keys_list_offset = m__io->read_u4le();
    m_number_of_values = m__io->read_u4le();
    m_values_list_offset = m__io->read_u4le();
    m_security_key_offset = m__io->read_u4le();
    m_class_name_offset = m__io->read_u4le();
    m_largest_sub_key_name_size = m__io->read_u4le();
    m_largest_sub_key_class_name_size = m__io->read_u4le();
    m_largest_value_name_size = m__io->read_u4le();
    m_largest_value_data_size = m__io->read_u4le();
    m_unknown2 = m__io->read_u4le();
    m_key_name_size = m__io->read_u2le();
    m_class_name_size = m__io->read_u2le();
    m_unknown_string_size = m__io->read_u4le();
    m_unknown_string = kaitai::kstream::bytes_to_str(m__io->read_bytes(unknown_string_size()), std::string("ascii"));
}

regf_t::hive_bin_cell_t::named_key_t::~named_key_t() {
    delete m_last_key_written_date_and_time;
}

regf_t::hive_bin_cell_t::sub_key_list_ri_t::sub_key_list_ri_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void regf_t::hive_bin_cell_t::sub_key_list_ri_t::_read() {
    m_count = m__io->read_u2le();
    int l_items = count();
    m_items = new std::vector<item_t*>();
    m_items->reserve(l_items);
    for (int i = 0; i < l_items; i++) {
        m_items->push_back(new item_t(m__io, this, m__root));
    }
}

regf_t::hive_bin_cell_t::sub_key_list_ri_t::~sub_key_list_ri_t() {
    for (std::vector<item_t*>::iterator it = m_items->begin(); it != m_items->end(); ++it) {
        delete *it;
    }
    delete m_items;
}

regf_t::hive_bin_cell_t::sub_key_list_ri_t::item_t::item_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t::sub_key_list_ri_t* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void regf_t::hive_bin_cell_t::sub_key_list_ri_t::item_t::_read() {
    m_sub_key_list_offset = m__io->read_u4le();
}

regf_t::hive_bin_cell_t::sub_key_list_ri_t::item_t::~item_t() {
}

int32_t regf_t::hive_bin_cell_t::cell_size() {
    if (f_cell_size)
        return m_cell_size;
    m_cell_size = (((cell_size_raw() < 0) ? (-1) : (1)) * cell_size_raw());
    f_cell_size = true;
    return m_cell_size;
}

bool regf_t::hive_bin_cell_t::is_allocated() {
    if (f_is_allocated)
        return m_is_allocated;
    m_is_allocated = cell_size_raw() < 0;
    f_is_allocated = true;
    return m_is_allocated;
}

regf_t::file_header_t::file_header_t(kaitai::kstream* p__io, regf_t* p__parent, regf_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void regf_t::file_header_t::_read() {
    m_signature = m__io->ensure_fixed_contents(std::string("\x72\x65\x67\x66", 4));
    m_primary_sequence_number = m__io->read_u4le();
    m_secondary_sequence_number = m__io->read_u4le();
    m_last_modification_date_and_time = new filetime_t(m__io, this, m__root);
    m_major_version = m__io->read_u4le();
    m_minor_version = m__io->read_u4le();
    m_type = static_cast<regf_t::file_header_t::file_type_t>(m__io->read_u4le());
    m_format = static_cast<regf_t::file_header_t::file_format_t>(m__io->read_u4le());
    m_root_key_offset = m__io->read_u4le();
    m_hive_bins_data_size = m__io->read_u4le();
    m_clustering_factor = m__io->read_u4le();
    m_unknown1 = m__io->read_bytes(64);
    m_unknown2 = m__io->read_bytes(396);
    m_checksum = m__io->read_u4le();
    m_reserved = m__io->read_bytes(3576);
    m_boot_type = m__io->read_u4le();
    m_boot_recover = m__io->read_u4le();
}

regf_t::file_header_t::~file_header_t() {
    delete m_last_modification_date_and_time;
}
