#ifndef REGF_H_
#define REGF_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"

#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 7000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.7 or later is required"
#endif

/**
 * This spec allows to parse files used by Microsoft Windows family of
 * operating systems to store parts of its "registry". "Registry" is a
 * hierarchical database that is used to store system settings (global
 * configuration, per-user, per-application configuration, etc).
 * 
 * Typically, registry files are stored in:
 * 
 * * System-wide: several files in `%SystemRoot%\System32\Config\`
 * * User-wide:
 *   * `%USERPROFILE%\Ntuser.dat`
 *   * `%USERPROFILE%\Local Settings\Application Data\Microsoft\Windows\Usrclass.dat` (localized, Windows 2000, Server 2003 and Windows XP)
 *   * `%USERPROFILE%\AppData\Local\Microsoft\Windows\Usrclass.dat` (non-localized, Windows Vista and later)
 * 
 * Note that one typically can't access files directly on a mounted
 * filesystem with a running Windows OS.
 * \sa Source
 */

class regf_t : public kaitai::kstruct {

public:
    class filetime_t;
    class hive_bin_t;
    class hive_bin_header_t;
    class hive_bin_cell_t;
    class file_header_t;

    regf_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, regf_t* p__root = 0);

private:
    void _read();

public:
    ~regf_t();

    class filetime_t : public kaitai::kstruct {

    public:

        filetime_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, regf_t* p__root = 0);

    private:
        void _read();

    public:
        ~filetime_t();

    private:
        uint64_t m_value;
        regf_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint64_t value() const { return m_value; }
        regf_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class hive_bin_t : public kaitai::kstruct {

    public:

        hive_bin_t(kaitai::kstream* p__io, regf_t* p__parent = 0, regf_t* p__root = 0);

    private:
        void _read();

    public:
        ~hive_bin_t();

    private:
        hive_bin_header_t* m_header;
        std::vector<hive_bin_cell_t*>* m_cells;
        regf_t* m__root;
        regf_t* m__parent;

    public:
        hive_bin_header_t* header() const { return m_header; }
        std::vector<hive_bin_cell_t*>* cells() const { return m_cells; }
        regf_t* _root() const { return m__root; }
        regf_t* _parent() const { return m__parent; }
    };

    class hive_bin_header_t : public kaitai::kstruct {

    public:

        hive_bin_header_t(kaitai::kstream* p__io, regf_t::hive_bin_t* p__parent = 0, regf_t* p__root = 0);

    private:
        void _read();

    public:
        ~hive_bin_header_t();

    private:
        std::string m_signature;
        uint32_t m_offset;
        uint32_t m_size;
        uint32_t m_unknown1;
        uint32_t m_unknown2;
        filetime_t* m_timestamp;
        uint32_t m_unknown4;
        regf_t* m__root;
        regf_t::hive_bin_t* m__parent;

    public:
        std::string signature() const { return m_signature; }

        /**
         * The offset of the hive bin, Value in bytes and relative from
         * the start of the hive bin data
         */
        uint32_t offset() const { return m_offset; }

        /**
         * Size of the hive bin
         */
        uint32_t size() const { return m_size; }

        /**
         * 0 most of the time, can contain remnant data
         */
        uint32_t unknown1() const { return m_unknown1; }

        /**
         * 0 most of the time, can contain remnant data
         */
        uint32_t unknown2() const { return m_unknown2; }

        /**
         * Only the root (first) hive bin seems to contain a valid FILETIME
         */
        filetime_t* timestamp() const { return m_timestamp; }

        /**
         * Contains number of bytes
         */
        uint32_t unknown4() const { return m_unknown4; }
        regf_t* _root() const { return m__root; }
        regf_t::hive_bin_t* _parent() const { return m__parent; }
    };

    class hive_bin_cell_t : public kaitai::kstruct {

    public:
        class sub_key_list_vk_t;
        class sub_key_list_lh_lf_t;
        class sub_key_list_sk_t;
        class sub_key_list_li_t;
        class named_key_t;
        class sub_key_list_ri_t;

        hive_bin_cell_t(kaitai::kstream* p__io, regf_t::hive_bin_t* p__parent = 0, regf_t* p__root = 0);

    private:
        void _read();

    public:
        ~hive_bin_cell_t();

        class sub_key_list_vk_t : public kaitai::kstruct {

        public:

            enum data_type_enum_t {
                DATA_TYPE_ENUM_REG_NONE = 0,
                DATA_TYPE_ENUM_REG_SZ = 1,
                DATA_TYPE_ENUM_REG_EXPAND_SZ = 2,
                DATA_TYPE_ENUM_REG_BINARY = 3,
                DATA_TYPE_ENUM_REG_DWORD = 4,
                DATA_TYPE_ENUM_REG_DWORD_BIG_ENDIAN = 5,
                DATA_TYPE_ENUM_REG_LINK = 6,
                DATA_TYPE_ENUM_REG_MULTI_SZ = 7,
                DATA_TYPE_ENUM_REG_RESOURCE_LIST = 8,
                DATA_TYPE_ENUM_REG_FULL_RESOURCE_DESCRIPTOR = 9,
                DATA_TYPE_ENUM_REG_RESOURCE_REQUIREMENTS_LIST = 10,
                DATA_TYPE_ENUM_REG_QWORD = 11
            };

            enum vk_flags_t {
                VK_FLAGS_VALUE_COMP_NAME = 1
            };

            sub_key_list_vk_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t* p__parent = 0, regf_t* p__root = 0);

        private:
            void _read();

        public:
            ~sub_key_list_vk_t();

        private:
            uint16_t m_value_name_size;
            uint32_t m_data_size;
            uint32_t m_data_offset;
            data_type_enum_t m_data_type;
            vk_flags_t m_flags;
            uint16_t m_padding;
            std::string m_value_name;
            bool n_value_name;

        public:
            bool _is_null_value_name() { value_name(); return n_value_name; };

        private:
            regf_t* m__root;
            regf_t::hive_bin_cell_t* m__parent;

        public:
            uint16_t value_name_size() const { return m_value_name_size; }
            uint32_t data_size() const { return m_data_size; }
            uint32_t data_offset() const { return m_data_offset; }
            data_type_enum_t data_type() const { return m_data_type; }
            vk_flags_t flags() const { return m_flags; }
            uint16_t padding() const { return m_padding; }
            std::string value_name() const { return m_value_name; }
            regf_t* _root() const { return m__root; }
            regf_t::hive_bin_cell_t* _parent() const { return m__parent; }
        };

        class sub_key_list_lh_lf_t : public kaitai::kstruct {

        public:
            class item_t;

            sub_key_list_lh_lf_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t* p__parent = 0, regf_t* p__root = 0);

        private:
            void _read();

        public:
            ~sub_key_list_lh_lf_t();

            class item_t : public kaitai::kstruct {

            public:

                item_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t* p__parent = 0, regf_t* p__root = 0);

            private:
                void _read();

            public:
                ~item_t();

            private:
                uint32_t m_named_key_offset;
                uint32_t m_hash_value;
                regf_t* m__root;
                regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t* m__parent;

            public:
                uint32_t named_key_offset() const { return m_named_key_offset; }
                uint32_t hash_value() const { return m_hash_value; }
                regf_t* _root() const { return m__root; }
                regf_t::hive_bin_cell_t::sub_key_list_lh_lf_t* _parent() const { return m__parent; }
            };

        private:
            uint16_t m_count;
            std::vector<item_t*>* m_items;
            regf_t* m__root;
            regf_t::hive_bin_cell_t* m__parent;

        public:
            uint16_t count() const { return m_count; }
            std::vector<item_t*>* items() const { return m_items; }
            regf_t* _root() const { return m__root; }
            regf_t::hive_bin_cell_t* _parent() const { return m__parent; }
        };

        class sub_key_list_sk_t : public kaitai::kstruct {

        public:

            sub_key_list_sk_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t* p__parent = 0, regf_t* p__root = 0);

        private:
            void _read();

        public:
            ~sub_key_list_sk_t();

        private:
            uint16_t m_unknown1;
            uint32_t m_previous_security_key_offset;
            uint32_t m_next_security_key_offset;
            uint32_t m_reference_count;
            regf_t* m__root;
            regf_t::hive_bin_cell_t* m__parent;

        public:
            uint16_t unknown1() const { return m_unknown1; }
            uint32_t previous_security_key_offset() const { return m_previous_security_key_offset; }
            uint32_t next_security_key_offset() const { return m_next_security_key_offset; }
            uint32_t reference_count() const { return m_reference_count; }
            regf_t* _root() const { return m__root; }
            regf_t::hive_bin_cell_t* _parent() const { return m__parent; }
        };

        class sub_key_list_li_t : public kaitai::kstruct {

        public:
            class item_t;

            sub_key_list_li_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t* p__parent = 0, regf_t* p__root = 0);

        private:
            void _read();

        public:
            ~sub_key_list_li_t();

            class item_t : public kaitai::kstruct {

            public:

                item_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t::sub_key_list_li_t* p__parent = 0, regf_t* p__root = 0);

            private:
                void _read();

            public:
                ~item_t();

            private:
                uint32_t m_named_key_offset;
                regf_t* m__root;
                regf_t::hive_bin_cell_t::sub_key_list_li_t* m__parent;

            public:
                uint32_t named_key_offset() const { return m_named_key_offset; }
                regf_t* _root() const { return m__root; }
                regf_t::hive_bin_cell_t::sub_key_list_li_t* _parent() const { return m__parent; }
            };

        private:
            uint16_t m_count;
            std::vector<item_t*>* m_items;
            regf_t* m__root;
            regf_t::hive_bin_cell_t* m__parent;

        public:
            uint16_t count() const { return m_count; }
            std::vector<item_t*>* items() const { return m_items; }
            regf_t* _root() const { return m__root; }
            regf_t::hive_bin_cell_t* _parent() const { return m__parent; }
        };

        class named_key_t : public kaitai::kstruct {

        public:

            enum nk_flags_t {
                NK_FLAGS_KEY_IS_VOLATILE = 1,
                NK_FLAGS_KEY_HIVE_EXIT = 2,
                NK_FLAGS_KEY_HIVE_ENTRY = 4,
                NK_FLAGS_KEY_NO_DELETE = 8,
                NK_FLAGS_KEY_SYM_LINK = 16,
                NK_FLAGS_KEY_COMP_NAME = 32,
                NK_FLAGS_KEY_PREFEF_HANDLE = 64,
                NK_FLAGS_KEY_VIRT_MIRRORED = 128,
                NK_FLAGS_KEY_VIRT_TARGET = 256,
                NK_FLAGS_KEY_VIRTUAL_STORE = 512,
                NK_FLAGS_UNKNOWN1 = 4096,
                NK_FLAGS_UNKNOWN2 = 16384
            };

            named_key_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t* p__parent = 0, regf_t* p__root = 0);

        private:
            void _read();

        public:
            ~named_key_t();

        private:
            nk_flags_t m_flags;
            filetime_t* m_last_key_written_date_and_time;
            uint32_t m_unknown1;
            uint32_t m_parent_key_offset;
            uint32_t m_number_of_sub_keys;
            uint32_t m_number_of_volatile_sub_keys;
            uint32_t m_sub_keys_list_offset;
            uint32_t m_number_of_values;
            uint32_t m_values_list_offset;
            uint32_t m_security_key_offset;
            uint32_t m_class_name_offset;
            uint32_t m_largest_sub_key_name_size;
            uint32_t m_largest_sub_key_class_name_size;
            uint32_t m_largest_value_name_size;
            uint32_t m_largest_value_data_size;
            uint32_t m_unknown2;
            uint16_t m_key_name_size;
            uint16_t m_class_name_size;
            uint32_t m_unknown_string_size;
            std::string m_unknown_string;
            regf_t* m__root;
            regf_t::hive_bin_cell_t* m__parent;

        public:
            nk_flags_t flags() const { return m_flags; }
            filetime_t* last_key_written_date_and_time() const { return m_last_key_written_date_and_time; }
            uint32_t unknown1() const { return m_unknown1; }
            uint32_t parent_key_offset() const { return m_parent_key_offset; }
            uint32_t number_of_sub_keys() const { return m_number_of_sub_keys; }
            uint32_t number_of_volatile_sub_keys() const { return m_number_of_volatile_sub_keys; }
            uint32_t sub_keys_list_offset() const { return m_sub_keys_list_offset; }
            uint32_t number_of_values() const { return m_number_of_values; }
            uint32_t values_list_offset() const { return m_values_list_offset; }
            uint32_t security_key_offset() const { return m_security_key_offset; }
            uint32_t class_name_offset() const { return m_class_name_offset; }
            uint32_t largest_sub_key_name_size() const { return m_largest_sub_key_name_size; }
            uint32_t largest_sub_key_class_name_size() const { return m_largest_sub_key_class_name_size; }
            uint32_t largest_value_name_size() const { return m_largest_value_name_size; }
            uint32_t largest_value_data_size() const { return m_largest_value_data_size; }
            uint32_t unknown2() const { return m_unknown2; }
            uint16_t key_name_size() const { return m_key_name_size; }
            uint16_t class_name_size() const { return m_class_name_size; }
            uint32_t unknown_string_size() const { return m_unknown_string_size; }
            std::string unknown_string() const { return m_unknown_string; }
            regf_t* _root() const { return m__root; }
            regf_t::hive_bin_cell_t* _parent() const { return m__parent; }
        };

        class sub_key_list_ri_t : public kaitai::kstruct {

        public:
            class item_t;

            sub_key_list_ri_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t* p__parent = 0, regf_t* p__root = 0);

        private:
            void _read();

        public:
            ~sub_key_list_ri_t();

            class item_t : public kaitai::kstruct {

            public:

                item_t(kaitai::kstream* p__io, regf_t::hive_bin_cell_t::sub_key_list_ri_t* p__parent = 0, regf_t* p__root = 0);

            private:
                void _read();

            public:
                ~item_t();

            private:
                uint32_t m_sub_key_list_offset;
                regf_t* m__root;
                regf_t::hive_bin_cell_t::sub_key_list_ri_t* m__parent;

            public:
                uint32_t sub_key_list_offset() const { return m_sub_key_list_offset; }
                regf_t* _root() const { return m__root; }
                regf_t::hive_bin_cell_t::sub_key_list_ri_t* _parent() const { return m__parent; }
            };

        private:
            uint16_t m_count;
            std::vector<item_t*>* m_items;
            regf_t* m__root;
            regf_t::hive_bin_cell_t* m__parent;

        public:
            uint16_t count() const { return m_count; }
            std::vector<item_t*>* items() const { return m_items; }
            regf_t* _root() const { return m__root; }
            regf_t::hive_bin_cell_t* _parent() const { return m__parent; }
        };

    private:
        bool f_cell_size;
        int32_t m_cell_size;

    public:
        int32_t cell_size();

    private:
        bool f_is_allocated;
        bool m_is_allocated;

    public:
        bool is_allocated();

    private:
        int32_t m_cell_size_raw;
        std::string m_identifier;
        kaitai::kstruct* m_data;
        bool n_data;

    public:
        bool _is_null_data() { data(); return n_data; };

    private:
        regf_t* m__root;
        regf_t::hive_bin_t* m__parent;
        std::string m__raw_data;
        kaitai::kstream* m__io__raw_data;

    public:
        int32_t cell_size_raw() const { return m_cell_size_raw; }
        std::string identifier() const { return m_identifier; }
        kaitai::kstruct* data() const { return m_data; }
        regf_t* _root() const { return m__root; }
        regf_t::hive_bin_t* _parent() const { return m__parent; }
        std::string _raw_data() const { return m__raw_data; }
        kaitai::kstream* _io__raw_data() const { return m__io__raw_data; }
    };

    class file_header_t : public kaitai::kstruct {

    public:

        enum file_type_t {
            FILE_TYPE_NORMAL = 0,
            FILE_TYPE_TRANSACTION_LOG = 1
        };

        enum file_format_t {
            FILE_FORMAT_DIRECT_MEMORY_LOAD = 1
        };

        file_header_t(kaitai::kstream* p__io, regf_t* p__parent = 0, regf_t* p__root = 0);

    private:
        void _read();

    public:
        ~file_header_t();

    private:
        std::string m_signature;
        uint32_t m_primary_sequence_number;
        uint32_t m_secondary_sequence_number;
        filetime_t* m_last_modification_date_and_time;
        uint32_t m_major_version;
        uint32_t m_minor_version;
        file_type_t m_type;
        file_format_t m_format;
        uint32_t m_root_key_offset;
        uint32_t m_hive_bins_data_size;
        uint32_t m_clustering_factor;
        std::string m_unknown1;
        std::string m_unknown2;
        uint32_t m_checksum;
        std::string m_reserved;
        uint32_t m_boot_type;
        uint32_t m_boot_recover;
        regf_t* m__root;
        regf_t* m__parent;

    public:
        std::string signature() const { return m_signature; }
        uint32_t primary_sequence_number() const { return m_primary_sequence_number; }
        uint32_t secondary_sequence_number() const { return m_secondary_sequence_number; }
        filetime_t* last_modification_date_and_time() const { return m_last_modification_date_and_time; }
        uint32_t major_version() const { return m_major_version; }
        uint32_t minor_version() const { return m_minor_version; }
        file_type_t type() const { return m_type; }
        file_format_t format() const { return m_format; }
        uint32_t root_key_offset() const { return m_root_key_offset; }
        uint32_t hive_bins_data_size() const { return m_hive_bins_data_size; }
        uint32_t clustering_factor() const { return m_clustering_factor; }
        std::string unknown1() const { return m_unknown1; }
        std::string unknown2() const { return m_unknown2; }
        uint32_t checksum() const { return m_checksum; }
        std::string reserved() const { return m_reserved; }
        uint32_t boot_type() const { return m_boot_type; }
        uint32_t boot_recover() const { return m_boot_recover; }
        regf_t* _root() const { return m__root; }
        regf_t* _parent() const { return m__parent; }
    };

private:
    file_header_t* m_header;
    std::vector<hive_bin_t*>* m_hive_bins;
    regf_t* m__root;
    kaitai::kstruct* m__parent;
    std::vector<std::string>* m__raw_hive_bins;
    std::vector<kaitai::kstream*>* m__io__raw_hive_bins;

public:
    file_header_t* header() const { return m_header; }
    std::vector<hive_bin_t*>* hive_bins() const { return m_hive_bins; }
    regf_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
    std::vector<std::string>* _raw_hive_bins() const { return m__raw_hive_bins; }
    std::vector<kaitai::kstream*>* _io__raw_hive_bins() const { return m__io__raw_hive_bins; }
};

#endif  // REGF_H_
