#ifndef WINDOWS_SHELL_ITEMS_H_
#define WINDOWS_SHELL_ITEMS_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"

#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 7000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.7 or later is required"
#endif

/**
 * Windows Shell Items (AKA "shellbags") is an undocumented set of
 * structures used internally within Windows to identify paths in
 * Windows Folder Hierarchy. It is widely used in Windows Shell (and
 * most visible in File Explorer), both as in-memory and in-file
 * structures. Some formats embed them, namely:
 * 
 * * Windows Shell link files (.lnk) Windows registry
 * * Windows registry "ShellBags" keys
 * 
 * The format is mostly undocumented, and is known to vary between
 * various Windows versions.
 * \sa Source
 */

class windows_shell_items_t : public kaitai::kstruct {

public:
    class shell_item_data_t;
    class shell_item_t;
    class root_folder_body_t;
    class volume_body_t;
    class file_entry_body_t;

    windows_shell_items_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, windows_shell_items_t* p__root = 0);

private:
    void _read();

public:
    ~windows_shell_items_t();

    class shell_item_data_t : public kaitai::kstruct {

    public:

        shell_item_data_t(kaitai::kstream* p__io, windows_shell_items_t::shell_item_t* p__parent = 0, windows_shell_items_t* p__root = 0);

    private:
        void _read();

    public:
        ~shell_item_data_t();

    private:
        uint8_t m_code;
        root_folder_body_t* m_body1;
        bool n_body1;

    public:
        bool _is_null_body1() { body1(); return n_body1; };

    private:
        kaitai::kstruct* m_body2;
        bool n_body2;

    public:
        bool _is_null_body2() { body2(); return n_body2; };

    private:
        windows_shell_items_t* m__root;
        windows_shell_items_t::shell_item_t* m__parent;

    public:
        uint8_t code() const { return m_code; }
        root_folder_body_t* body1() const { return m_body1; }
        kaitai::kstruct* body2() const { return m_body2; }
        windows_shell_items_t* _root() const { return m__root; }
        windows_shell_items_t::shell_item_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Section 2.2.2
     */

    class shell_item_t : public kaitai::kstruct {

    public:

        shell_item_t(kaitai::kstream* p__io, windows_shell_items_t* p__parent = 0, windows_shell_items_t* p__root = 0);

    private:
        void _read();

    public:
        ~shell_item_t();

    private:
        uint16_t m_len_data;
        shell_item_data_t* m_data;
        bool n_data;

    public:
        bool _is_null_data() { data(); return n_data; };

    private:
        windows_shell_items_t* m__root;
        windows_shell_items_t* m__parent;
        std::string m__raw_data;
        kaitai::kstream* m__io__raw_data;

    public:
        uint16_t len_data() const { return m_len_data; }
        shell_item_data_t* data() const { return m_data; }
        windows_shell_items_t* _root() const { return m__root; }
        windows_shell_items_t* _parent() const { return m__parent; }
        std::string _raw_data() const { return m__raw_data; }
        kaitai::kstream* _io__raw_data() const { return m__io__raw_data; }
    };

    /**
     * \sa Source
     */

    class root_folder_body_t : public kaitai::kstruct {

    public:

        root_folder_body_t(kaitai::kstream* p__io, windows_shell_items_t::shell_item_data_t* p__parent = 0, windows_shell_items_t* p__root = 0);

    private:
        void _read();

    public:
        ~root_folder_body_t();

    private:
        uint8_t m_sort_index;
        std::string m_shell_folder_id;
        windows_shell_items_t* m__root;
        windows_shell_items_t::shell_item_data_t* m__parent;

    public:
        uint8_t sort_index() const { return m_sort_index; }
        std::string shell_folder_id() const { return m_shell_folder_id; }
        windows_shell_items_t* _root() const { return m__root; }
        windows_shell_items_t::shell_item_data_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class volume_body_t : public kaitai::kstruct {

    public:

        volume_body_t(kaitai::kstream* p__io, windows_shell_items_t::shell_item_data_t* p__parent = 0, windows_shell_items_t* p__root = 0);

    private:
        void _read();

    public:
        ~volume_body_t();

    private:
        uint8_t m_flags;
        windows_shell_items_t* m__root;
        windows_shell_items_t::shell_item_data_t* m__parent;

    public:
        uint8_t flags() const { return m_flags; }
        windows_shell_items_t* _root() const { return m__root; }
        windows_shell_items_t::shell_item_data_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class file_entry_body_t : public kaitai::kstruct {

    public:

        file_entry_body_t(kaitai::kstream* p__io, windows_shell_items_t::shell_item_data_t* p__parent = 0, windows_shell_items_t* p__root = 0);

    private:
        void _read();

    public:
        ~file_entry_body_t();

    private:
        bool f_is_dir;
        bool m_is_dir;

    public:
        bool is_dir();

    private:
        bool f_is_file;
        bool m_is_file;

    public:
        bool is_file();

    private:
        uint8_t m__unnamed0;
        uint32_t m_file_size;
        uint32_t m_last_mod_time;
        uint16_t m_file_attrs;
        windows_shell_items_t* m__root;
        windows_shell_items_t::shell_item_data_t* m__parent;

    public:
        uint8_t _unnamed0() const { return m__unnamed0; }
        uint32_t file_size() const { return m_file_size; }
        uint32_t last_mod_time() const { return m_last_mod_time; }
        uint16_t file_attrs() const { return m_file_attrs; }
        windows_shell_items_t* _root() const { return m__root; }
        windows_shell_items_t::shell_item_data_t* _parent() const { return m__parent; }
    };

private:
    std::vector<shell_item_t*>* m_items;
    windows_shell_items_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * \sa Section 2.2.1
     */
    std::vector<shell_item_t*>* items() const { return m_items; }
    windows_shell_items_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // WINDOWS_SHELL_ITEMS_H_
