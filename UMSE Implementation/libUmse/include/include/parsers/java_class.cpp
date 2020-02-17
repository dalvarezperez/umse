// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "java_class.h"



java_class_t::java_class_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    _read();
}

void java_class_t::_read() {
    m_magic = m__io->ensure_fixed_contents(std::string("\xCA\xFE\xBA\xBE", 4));
    m_version_minor = m__io->read_u2be();
    m_version_major = m__io->read_u2be();
    m_constant_pool_count = m__io->read_u2be();
    int l_constant_pool = (constant_pool_count() - 1);
    m_constant_pool = new std::vector<constant_pool_entry_t*>();
    m_constant_pool->reserve(l_constant_pool);
    for (int i = 0; i < l_constant_pool; i++) {
        m_constant_pool->push_back(new constant_pool_entry_t(m__io, this, m__root));
    }
    m_access_flags = m__io->read_u2be();
    m_this_class = m__io->read_u2be();
    m_super_class = m__io->read_u2be();
    m_interfaces_count = m__io->read_u2be();
    int l_interfaces = interfaces_count();
    m_interfaces = new std::vector<uint16_t>();
    m_interfaces->reserve(l_interfaces);
    for (int i = 0; i < l_interfaces; i++) {
        m_interfaces->push_back(m__io->read_u2be());
    }
    m_fields_count = m__io->read_u2be();
    int l_fields = fields_count();
    m_fields = new std::vector<field_info_t*>();
    m_fields->reserve(l_fields);
    for (int i = 0; i < l_fields; i++) {
        m_fields->push_back(new field_info_t(m__io, this, m__root));
    }
    m_methods_count = m__io->read_u2be();
    int l_methods = methods_count();
    m_methods = new std::vector<method_info_t*>();
    m_methods->reserve(l_methods);
    for (int i = 0; i < l_methods; i++) {
        m_methods->push_back(new method_info_t(m__io, this, m__root));
    }
    m_attributes_count = m__io->read_u2be();
    int l_attributes = attributes_count();
    m_attributes = new std::vector<attribute_info_t*>();
    m_attributes->reserve(l_attributes);
    for (int i = 0; i < l_attributes; i++) {
        m_attributes->push_back(new attribute_info_t(m__io, this, m__root));
    }
}

java_class_t::~java_class_t() {
    for (std::vector<constant_pool_entry_t*>::iterator it = m_constant_pool->begin(); it != m_constant_pool->end(); ++it) {
        delete *it;
    }
    delete m_constant_pool;
    delete m_interfaces;
    for (std::vector<field_info_t*>::iterator it = m_fields->begin(); it != m_fields->end(); ++it) {
        delete *it;
    }
    delete m_fields;
    for (std::vector<method_info_t*>::iterator it = m_methods->begin(); it != m_methods->end(); ++it) {
        delete *it;
    }
    delete m_methods;
    for (std::vector<attribute_info_t*>::iterator it = m_attributes->begin(); it != m_attributes->end(); ++it) {
        delete *it;
    }
    delete m_attributes;
}

java_class_t::float_cp_info_t::float_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::float_cp_info_t::_read() {
    m_value = m__io->read_f4be();
}

java_class_t::float_cp_info_t::~float_cp_info_t() {
}

java_class_t::attribute_info_t::attribute_info_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_name_as_str = false;
    _read();
}

void java_class_t::attribute_info_t::_read() {
    m_name_index = m__io->read_u2be();
    m_attribute_length = m__io->read_u4be();
    n_info = true;
    {
        std::string on = name_as_str();
        if (on == std::string("SourceFile")) {
            n_info = false;
            m__raw_info = m__io->read_bytes(attribute_length());
            m__io__raw_info = new kaitai::kstream(m__raw_info);
            m_info = new attr_body_source_file_t(m__io__raw_info, this, m__root);
        }
        else if (on == std::string("LineNumberTable")) {
            n_info = false;
            m__raw_info = m__io->read_bytes(attribute_length());
            m__io__raw_info = new kaitai::kstream(m__raw_info);
            m_info = new attr_body_line_number_table_t(m__io__raw_info, this, m__root);
        }
        else if (on == std::string("Exceptions")) {
            n_info = false;
            m__raw_info = m__io->read_bytes(attribute_length());
            m__io__raw_info = new kaitai::kstream(m__raw_info);
            m_info = new attr_body_exceptions_t(m__io__raw_info, this, m__root);
        }
        else if (on == std::string("Code")) {
            n_info = false;
            m__raw_info = m__io->read_bytes(attribute_length());
            m__io__raw_info = new kaitai::kstream(m__raw_info);
            m_info = new attr_body_code_t(m__io__raw_info, this, m__root);
        }
        else {
            m__raw_info = m__io->read_bytes(attribute_length());
        }
    }
}

java_class_t::attribute_info_t::~attribute_info_t() {
    if (!n_info) {
        delete m__io__raw_info;
        delete m_info;
    }
}

java_class_t::attribute_info_t::attr_body_code_t::attr_body_code_t(kaitai::kstream* p__io, java_class_t::attribute_info_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::attribute_info_t::attr_body_code_t::_read() {
    m_max_stack = m__io->read_u2be();
    m_max_locals = m__io->read_u2be();
    m_code_length = m__io->read_u4be();
    m_code = m__io->read_bytes(code_length());
    m_exception_table_length = m__io->read_u2be();
    int l_exception_table = exception_table_length();
    m_exception_table = new std::vector<exception_entry_t*>();
    m_exception_table->reserve(l_exception_table);
    for (int i = 0; i < l_exception_table; i++) {
        m_exception_table->push_back(new exception_entry_t(m__io, this, m__root));
    }
    m_attributes_count = m__io->read_u2be();
    int l_attributes = attributes_count();
    m_attributes = new std::vector<attribute_info_t*>();
    m_attributes->reserve(l_attributes);
    for (int i = 0; i < l_attributes; i++) {
        m_attributes->push_back(new attribute_info_t(m__io, this, m__root));
    }
}

java_class_t::attribute_info_t::attr_body_code_t::~attr_body_code_t() {
    for (std::vector<exception_entry_t*>::iterator it = m_exception_table->begin(); it != m_exception_table->end(); ++it) {
        delete *it;
    }
    delete m_exception_table;
    for (std::vector<attribute_info_t*>::iterator it = m_attributes->begin(); it != m_attributes->end(); ++it) {
        delete *it;
    }
    delete m_attributes;
}

java_class_t::attribute_info_t::attr_body_code_t::exception_entry_t::exception_entry_t(kaitai::kstream* p__io, java_class_t::attribute_info_t::attr_body_code_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_catch_exception = false;
    _read();
}

void java_class_t::attribute_info_t::attr_body_code_t::exception_entry_t::_read() {
    m_start_pc = m__io->read_u2be();
    m_end_pc = m__io->read_u2be();
    m_handler_pc = m__io->read_u2be();
    m_catch_type = m__io->read_u2be();
}

java_class_t::attribute_info_t::attr_body_code_t::exception_entry_t::~exception_entry_t() {
}

java_class_t::constant_pool_entry_t* java_class_t::attribute_info_t::attr_body_code_t::exception_entry_t::catch_exception() {
    if (f_catch_exception)
        return m_catch_exception;
    n_catch_exception = true;
    if (catch_type() != 0) {
        n_catch_exception = false;
        m_catch_exception = _root()->constant_pool()->at((catch_type() - 1));
    }
    f_catch_exception = true;
    return m_catch_exception;
}

java_class_t::attribute_info_t::attr_body_exceptions_t::attr_body_exceptions_t(kaitai::kstream* p__io, java_class_t::attribute_info_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::attribute_info_t::attr_body_exceptions_t::_read() {
    m_number_of_exceptions = m__io->read_u2be();
    int l_exceptions = number_of_exceptions();
    m_exceptions = new std::vector<exception_table_entry_t*>();
    m_exceptions->reserve(l_exceptions);
    for (int i = 0; i < l_exceptions; i++) {
        m_exceptions->push_back(new exception_table_entry_t(m__io, this, m__root));
    }
}

java_class_t::attribute_info_t::attr_body_exceptions_t::~attr_body_exceptions_t() {
    for (std::vector<exception_table_entry_t*>::iterator it = m_exceptions->begin(); it != m_exceptions->end(); ++it) {
        delete *it;
    }
    delete m_exceptions;
}

java_class_t::attribute_info_t::attr_body_exceptions_t::exception_table_entry_t::exception_table_entry_t(kaitai::kstream* p__io, java_class_t::attribute_info_t::attr_body_exceptions_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_as_info = false;
    f_name_as_str = false;
    _read();
}

void java_class_t::attribute_info_t::attr_body_exceptions_t::exception_table_entry_t::_read() {
    m_index = m__io->read_u2be();
}

java_class_t::attribute_info_t::attr_body_exceptions_t::exception_table_entry_t::~exception_table_entry_t() {
}

java_class_t::class_cp_info_t* java_class_t::attribute_info_t::attr_body_exceptions_t::exception_table_entry_t::as_info() {
    if (f_as_info)
        return m_as_info;
    m_as_info = static_cast<class_cp_info_t*>(_root()->constant_pool()->at((index() - 1))->cp_info());
    f_as_info = true;
    return m_as_info;
}

std::string java_class_t::attribute_info_t::attr_body_exceptions_t::exception_table_entry_t::name_as_str() {
    if (f_name_as_str)
        return m_name_as_str;
    m_name_as_str = as_info()->name_as_str();
    f_name_as_str = true;
    return m_name_as_str;
}

java_class_t::attribute_info_t::attr_body_source_file_t::attr_body_source_file_t(kaitai::kstream* p__io, java_class_t::attribute_info_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_sourcefile_as_str = false;
    _read();
}

void java_class_t::attribute_info_t::attr_body_source_file_t::_read() {
    m_sourcefile_index = m__io->read_u2be();
}

java_class_t::attribute_info_t::attr_body_source_file_t::~attr_body_source_file_t() {
}

std::string java_class_t::attribute_info_t::attr_body_source_file_t::sourcefile_as_str() {
    if (f_sourcefile_as_str)
        return m_sourcefile_as_str;
    m_sourcefile_as_str = static_cast<utf8_cp_info_t*>(_root()->constant_pool()->at((sourcefile_index() - 1))->cp_info())->value();
    f_sourcefile_as_str = true;
    return m_sourcefile_as_str;
}

java_class_t::attribute_info_t::attr_body_line_number_table_t::attr_body_line_number_table_t(kaitai::kstream* p__io, java_class_t::attribute_info_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::attribute_info_t::attr_body_line_number_table_t::_read() {
    m_line_number_table_length = m__io->read_u2be();
    int l_line_number_table = line_number_table_length();
    m_line_number_table = new std::vector<line_number_table_entry_t*>();
    m_line_number_table->reserve(l_line_number_table);
    for (int i = 0; i < l_line_number_table; i++) {
        m_line_number_table->push_back(new line_number_table_entry_t(m__io, this, m__root));
    }
}

java_class_t::attribute_info_t::attr_body_line_number_table_t::~attr_body_line_number_table_t() {
    for (std::vector<line_number_table_entry_t*>::iterator it = m_line_number_table->begin(); it != m_line_number_table->end(); ++it) {
        delete *it;
    }
    delete m_line_number_table;
}

java_class_t::attribute_info_t::attr_body_line_number_table_t::line_number_table_entry_t::line_number_table_entry_t(kaitai::kstream* p__io, java_class_t::attribute_info_t::attr_body_line_number_table_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::attribute_info_t::attr_body_line_number_table_t::line_number_table_entry_t::_read() {
    m_start_pc = m__io->read_u2be();
    m_line_number = m__io->read_u2be();
}

java_class_t::attribute_info_t::attr_body_line_number_table_t::line_number_table_entry_t::~line_number_table_entry_t() {
}

std::string java_class_t::attribute_info_t::name_as_str() {
    if (f_name_as_str)
        return m_name_as_str;
    m_name_as_str = static_cast<utf8_cp_info_t*>(_root()->constant_pool()->at((name_index() - 1))->cp_info())->value();
    f_name_as_str = true;
    return m_name_as_str;
}

java_class_t::method_ref_cp_info_t::method_ref_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_class_as_info = false;
    f_name_and_type_as_info = false;
    _read();
}

void java_class_t::method_ref_cp_info_t::_read() {
    m_class_index = m__io->read_u2be();
    m_name_and_type_index = m__io->read_u2be();
}

java_class_t::method_ref_cp_info_t::~method_ref_cp_info_t() {
}

java_class_t::class_cp_info_t* java_class_t::method_ref_cp_info_t::class_as_info() {
    if (f_class_as_info)
        return m_class_as_info;
    m_class_as_info = static_cast<class_cp_info_t*>(_root()->constant_pool()->at((class_index() - 1))->cp_info());
    f_class_as_info = true;
    return m_class_as_info;
}

java_class_t::name_and_type_cp_info_t* java_class_t::method_ref_cp_info_t::name_and_type_as_info() {
    if (f_name_and_type_as_info)
        return m_name_and_type_as_info;
    m_name_and_type_as_info = static_cast<name_and_type_cp_info_t*>(_root()->constant_pool()->at((name_and_type_index() - 1))->cp_info());
    f_name_and_type_as_info = true;
    return m_name_and_type_as_info;
}

java_class_t::field_info_t::field_info_t(kaitai::kstream* p__io, java_class_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_name_as_str = false;
    _read();
}

void java_class_t::field_info_t::_read() {
    m_access_flags = m__io->read_u2be();
    m_name_index = m__io->read_u2be();
    m_descriptor_index = m__io->read_u2be();
    m_attributes_count = m__io->read_u2be();
    int l_attributes = attributes_count();
    m_attributes = new std::vector<attribute_info_t*>();
    m_attributes->reserve(l_attributes);
    for (int i = 0; i < l_attributes; i++) {
        m_attributes->push_back(new attribute_info_t(m__io, this, m__root));
    }
}

java_class_t::field_info_t::~field_info_t() {
    for (std::vector<attribute_info_t*>::iterator it = m_attributes->begin(); it != m_attributes->end(); ++it) {
        delete *it;
    }
    delete m_attributes;
}

std::string java_class_t::field_info_t::name_as_str() {
    if (f_name_as_str)
        return m_name_as_str;
    m_name_as_str = static_cast<utf8_cp_info_t*>(_root()->constant_pool()->at((name_index() - 1))->cp_info())->value();
    f_name_as_str = true;
    return m_name_as_str;
}

java_class_t::double_cp_info_t::double_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::double_cp_info_t::_read() {
    m_value = m__io->read_f8be();
}

java_class_t::double_cp_info_t::~double_cp_info_t() {
}

java_class_t::long_cp_info_t::long_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::long_cp_info_t::_read() {
    m_value = m__io->read_u8be();
}

java_class_t::long_cp_info_t::~long_cp_info_t() {
}

java_class_t::invoke_dynamic_cp_info_t::invoke_dynamic_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::invoke_dynamic_cp_info_t::_read() {
    m_bootstrap_method_attr_index = m__io->read_u2be();
    m_name_and_type_index = m__io->read_u2be();
}

java_class_t::invoke_dynamic_cp_info_t::~invoke_dynamic_cp_info_t() {
}

java_class_t::method_handle_cp_info_t::method_handle_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::method_handle_cp_info_t::_read() {
    m_reference_kind = static_cast<java_class_t::method_handle_cp_info_t::reference_kind_enum_t>(m__io->read_u1());
    m_reference_index = m__io->read_u2be();
}

java_class_t::method_handle_cp_info_t::~method_handle_cp_info_t() {
}

java_class_t::name_and_type_cp_info_t::name_and_type_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_name_as_info = false;
    f_name_as_str = false;
    f_descriptor_as_info = false;
    f_descriptor_as_str = false;
    _read();
}

void java_class_t::name_and_type_cp_info_t::_read() {
    m_name_index = m__io->read_u2be();
    m_descriptor_index = m__io->read_u2be();
}

java_class_t::name_and_type_cp_info_t::~name_and_type_cp_info_t() {
}

java_class_t::utf8_cp_info_t* java_class_t::name_and_type_cp_info_t::name_as_info() {
    if (f_name_as_info)
        return m_name_as_info;
    m_name_as_info = static_cast<utf8_cp_info_t*>(_root()->constant_pool()->at((name_index() - 1))->cp_info());
    f_name_as_info = true;
    return m_name_as_info;
}

std::string java_class_t::name_and_type_cp_info_t::name_as_str() {
    if (f_name_as_str)
        return m_name_as_str;
    m_name_as_str = name_as_info()->value();
    f_name_as_str = true;
    return m_name_as_str;
}

java_class_t::utf8_cp_info_t* java_class_t::name_and_type_cp_info_t::descriptor_as_info() {
    if (f_descriptor_as_info)
        return m_descriptor_as_info;
    m_descriptor_as_info = static_cast<utf8_cp_info_t*>(_root()->constant_pool()->at((descriptor_index() - 1))->cp_info());
    f_descriptor_as_info = true;
    return m_descriptor_as_info;
}

std::string java_class_t::name_and_type_cp_info_t::descriptor_as_str() {
    if (f_descriptor_as_str)
        return m_descriptor_as_str;
    m_descriptor_as_str = descriptor_as_info()->value();
    f_descriptor_as_str = true;
    return m_descriptor_as_str;
}

java_class_t::utf8_cp_info_t::utf8_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::utf8_cp_info_t::_read() {
    m_str_len = m__io->read_u2be();
    m_value = kaitai::kstream::bytes_to_str(m__io->read_bytes(str_len()), std::string("UTF-8"));
}

java_class_t::utf8_cp_info_t::~utf8_cp_info_t() {
}

java_class_t::string_cp_info_t::string_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::string_cp_info_t::_read() {
    m_string_index = m__io->read_u2be();
}

java_class_t::string_cp_info_t::~string_cp_info_t() {
}

java_class_t::method_type_cp_info_t::method_type_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::method_type_cp_info_t::_read() {
    m_descriptor_index = m__io->read_u2be();
}

java_class_t::method_type_cp_info_t::~method_type_cp_info_t() {
}

java_class_t::interface_method_ref_cp_info_t::interface_method_ref_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_class_as_info = false;
    f_name_and_type_as_info = false;
    _read();
}

void java_class_t::interface_method_ref_cp_info_t::_read() {
    m_class_index = m__io->read_u2be();
    m_name_and_type_index = m__io->read_u2be();
}

java_class_t::interface_method_ref_cp_info_t::~interface_method_ref_cp_info_t() {
}

java_class_t::class_cp_info_t* java_class_t::interface_method_ref_cp_info_t::class_as_info() {
    if (f_class_as_info)
        return m_class_as_info;
    m_class_as_info = static_cast<class_cp_info_t*>(_root()->constant_pool()->at((class_index() - 1))->cp_info());
    f_class_as_info = true;
    return m_class_as_info;
}

java_class_t::name_and_type_cp_info_t* java_class_t::interface_method_ref_cp_info_t::name_and_type_as_info() {
    if (f_name_and_type_as_info)
        return m_name_and_type_as_info;
    m_name_and_type_as_info = static_cast<name_and_type_cp_info_t*>(_root()->constant_pool()->at((name_and_type_index() - 1))->cp_info());
    f_name_and_type_as_info = true;
    return m_name_and_type_as_info;
}

java_class_t::class_cp_info_t::class_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_name_as_info = false;
    f_name_as_str = false;
    _read();
}

void java_class_t::class_cp_info_t::_read() {
    m_name_index = m__io->read_u2be();
}

java_class_t::class_cp_info_t::~class_cp_info_t() {
}

java_class_t::utf8_cp_info_t* java_class_t::class_cp_info_t::name_as_info() {
    if (f_name_as_info)
        return m_name_as_info;
    m_name_as_info = static_cast<utf8_cp_info_t*>(_root()->constant_pool()->at((name_index() - 1))->cp_info());
    f_name_as_info = true;
    return m_name_as_info;
}

std::string java_class_t::class_cp_info_t::name_as_str() {
    if (f_name_as_str)
        return m_name_as_str;
    m_name_as_str = name_as_info()->value();
    f_name_as_str = true;
    return m_name_as_str;
}

java_class_t::constant_pool_entry_t::constant_pool_entry_t(kaitai::kstream* p__io, java_class_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::constant_pool_entry_t::_read() {
    m_tag = static_cast<java_class_t::constant_pool_entry_t::tag_enum_t>(m__io->read_u1());
    n_cp_info = true;
    switch (tag()) {
    case TAG_ENUM_STRING: {
        n_cp_info = false;
        m_cp_info = new string_cp_info_t(m__io, this, m__root);
        break;
    }
    case TAG_ENUM_DOUBLE: {
        n_cp_info = false;
        m_cp_info = new double_cp_info_t(m__io, this, m__root);
        break;
    }
    case TAG_ENUM_INVOKE_DYNAMIC: {
        n_cp_info = false;
        m_cp_info = new invoke_dynamic_cp_info_t(m__io, this, m__root);
        break;
    }
    case TAG_ENUM_METHOD_HANDLE: {
        n_cp_info = false;
        m_cp_info = new method_handle_cp_info_t(m__io, this, m__root);
        break;
    }
    case TAG_ENUM_CLASS_TYPE: {
        n_cp_info = false;
        m_cp_info = new class_cp_info_t(m__io, this, m__root);
        break;
    }
    case TAG_ENUM_METHOD_REF: {
        n_cp_info = false;
        m_cp_info = new method_ref_cp_info_t(m__io, this, m__root);
        break;
    }
    case TAG_ENUM_LONG: {
        n_cp_info = false;
        m_cp_info = new long_cp_info_t(m__io, this, m__root);
        break;
    }
    case TAG_ENUM_NAME_AND_TYPE: {
        n_cp_info = false;
        m_cp_info = new name_and_type_cp_info_t(m__io, this, m__root);
        break;
    }
    case TAG_ENUM_FLOAT: {
        n_cp_info = false;
        m_cp_info = new float_cp_info_t(m__io, this, m__root);
        break;
    }
    case TAG_ENUM_INTERFACE_METHOD_REF: {
        n_cp_info = false;
        m_cp_info = new interface_method_ref_cp_info_t(m__io, this, m__root);
        break;
    }
    case TAG_ENUM_INTEGER: {
        n_cp_info = false;
        m_cp_info = new integer_cp_info_t(m__io, this, m__root);
        break;
    }
    case TAG_ENUM_UTF8: {
        n_cp_info = false;
        m_cp_info = new utf8_cp_info_t(m__io, this, m__root);
        break;
    }
    case TAG_ENUM_FIELD_REF: {
        n_cp_info = false;
        m_cp_info = new field_ref_cp_info_t(m__io, this, m__root);
        break;
    }
    case TAG_ENUM_METHOD_TYPE: {
        n_cp_info = false;
        m_cp_info = new method_type_cp_info_t(m__io, this, m__root);
        break;
    }
    }
}

java_class_t::constant_pool_entry_t::~constant_pool_entry_t() {
    if (!n_cp_info) {
        delete m_cp_info;
    }
}

java_class_t::method_info_t::method_info_t(kaitai::kstream* p__io, java_class_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_name_as_str = false;
    _read();
}

void java_class_t::method_info_t::_read() {
    m_access_flags = m__io->read_u2be();
    m_name_index = m__io->read_u2be();
    m_descriptor_index = m__io->read_u2be();
    m_attributes_count = m__io->read_u2be();
    int l_attributes = attributes_count();
    m_attributes = new std::vector<attribute_info_t*>();
    m_attributes->reserve(l_attributes);
    for (int i = 0; i < l_attributes; i++) {
        m_attributes->push_back(new attribute_info_t(m__io, this, m__root));
    }
}

java_class_t::method_info_t::~method_info_t() {
    for (std::vector<attribute_info_t*>::iterator it = m_attributes->begin(); it != m_attributes->end(); ++it) {
        delete *it;
    }
    delete m_attributes;
}

std::string java_class_t::method_info_t::name_as_str() {
    if (f_name_as_str)
        return m_name_as_str;
    m_name_as_str = static_cast<utf8_cp_info_t*>(_root()->constant_pool()->at((name_index() - 1))->cp_info())->value();
    f_name_as_str = true;
    return m_name_as_str;
}

java_class_t::integer_cp_info_t::integer_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void java_class_t::integer_cp_info_t::_read() {
    m_value = m__io->read_u4be();
}

java_class_t::integer_cp_info_t::~integer_cp_info_t() {
}

java_class_t::field_ref_cp_info_t::field_ref_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent, java_class_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_class_as_info = false;
    f_name_and_type_as_info = false;
    _read();
}

void java_class_t::field_ref_cp_info_t::_read() {
    m_class_index = m__io->read_u2be();
    m_name_and_type_index = m__io->read_u2be();
}

java_class_t::field_ref_cp_info_t::~field_ref_cp_info_t() {
}

java_class_t::class_cp_info_t* java_class_t::field_ref_cp_info_t::class_as_info() {
    if (f_class_as_info)
        return m_class_as_info;
    m_class_as_info = static_cast<class_cp_info_t*>(_root()->constant_pool()->at((class_index() - 1))->cp_info());
    f_class_as_info = true;
    return m_class_as_info;
}

java_class_t::name_and_type_cp_info_t* java_class_t::field_ref_cp_info_t::name_and_type_as_info() {
    if (f_name_and_type_as_info)
        return m_name_and_type_as_info;
    m_name_and_type_as_info = static_cast<name_and_type_cp_info_t*>(_root()->constant_pool()->at((name_and_type_index() - 1))->cp_info());
    f_name_and_type_as_info = true;
    return m_name_and_type_as_info;
}
