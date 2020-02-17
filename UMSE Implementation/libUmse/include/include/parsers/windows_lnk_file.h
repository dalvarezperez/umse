#ifndef WINDOWS_LNK_FILE_H_
#define WINDOWS_LNK_FILE_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"

#include <stdint.h>

#if KAITAI_STRUCT_VERSION < 7000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.7 or later is required"
#endif
class windows_shell_items_t;

/**
 * Windows .lnk files (AKA "shell link" file) are most frequently used
 * in Windows shell to create "shortcuts" to another files, usually for
 * purposes of running a program from some other directory, sometimes
 * with certain preconfigured arguments and some other options.
 * \sa Source
 */

class windows_lnk_file_t : public kaitai::kstruct {

public:
    class link_target_id_list_t;
    class string_data_t;
    class link_info_t;
    class link_flags_t;
    class file_header_t;

    enum window_state_t {
        WINDOW_STATE_NORMAL = 1,
        WINDOW_STATE_MAXIMIZED = 3,
        WINDOW_STATE_MIN_NO_ACTIVE = 7
    };

    enum drive_types_t {
        DRIVE_TYPES_UNKNOWN = 0,
        DRIVE_TYPES_NO_ROOT_DIR = 1,
        DRIVE_TYPES_REMOVABLE = 2,
        DRIVE_TYPES_FIXED = 3,
        DRIVE_TYPES_REMOTE = 4,
        DRIVE_TYPES_CDROM = 5,
        DRIVE_TYPES_RAMDISK = 6
    };

    windows_lnk_file_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, windows_lnk_file_t* p__root = 0);

private:
    void _read();

public:
    ~windows_lnk_file_t();

    /**
     * \sa Section 2.2
     */

    class link_target_id_list_t : public kaitai::kstruct {

    public:

        link_target_id_list_t(kaitai::kstream* p__io, windows_lnk_file_t* p__parent = 0, windows_lnk_file_t* p__root = 0);

    private:
        void _read();

    public:
        ~link_target_id_list_t();

    private:
        uint16_t m_len_id_list;
        windows_shell_items_t* m_id_list;
        windows_lnk_file_t* m__root;
        windows_lnk_file_t* m__parent;
        std::string m__raw_id_list;
        kaitai::kstream* m__io__raw_id_list;

    public:
        uint16_t len_id_list() const { return m_len_id_list; }
        windows_shell_items_t* id_list() const { return m_id_list; }
        windows_lnk_file_t* _root() const { return m__root; }
        windows_lnk_file_t* _parent() const { return m__parent; }
        std::string _raw_id_list() const { return m__raw_id_list; }
        kaitai::kstream* _io__raw_id_list() const { return m__io__raw_id_list; }
    };

    class string_data_t : public kaitai::kstruct {

    public:

        string_data_t(kaitai::kstream* p__io, windows_lnk_file_t* p__parent = 0, windows_lnk_file_t* p__root = 0);

    private:
        void _read();

    public:
        ~string_data_t();

    private:
        uint16_t m_chars_str;
        std::string m_str;
        windows_lnk_file_t* m__root;
        windows_lnk_file_t* m__parent;

    public:
        uint16_t chars_str() const { return m_chars_str; }
        std::string str() const { return m_str; }
        windows_lnk_file_t* _root() const { return m__root; }
        windows_lnk_file_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Section 2.3
     */

    class link_info_t : public kaitai::kstruct {

    public:
        class volume_id_body_t;
        class all_t;
        class volume_id_spec_t;
        class link_info_flags_t;
        class header_t;

        link_info_t(kaitai::kstream* p__io, windows_lnk_file_t* p__parent = 0, windows_lnk_file_t* p__root = 0);

    private:
        void _read();

    public:
        ~link_info_t();

        /**
         * \sa Section 2.3.1
         */

        class volume_id_body_t : public kaitai::kstruct {

        public:

            volume_id_body_t(kaitai::kstream* p__io, windows_lnk_file_t::link_info_t::volume_id_spec_t* p__parent = 0, windows_lnk_file_t* p__root = 0);

        private:
            void _read();

        public:
            ~volume_id_body_t();

        private:
            bool f_is_unicode;
            bool m_is_unicode;

        public:
            bool is_unicode();

        private:
            bool f_volume_label_ansi;
            std::string m_volume_label_ansi;
            bool n_volume_label_ansi;

        public:
            bool _is_null_volume_label_ansi() { volume_label_ansi(); return n_volume_label_ansi; };

        private:

        public:
            std::string volume_label_ansi();

        private:
            drive_types_t m_drive_type;
            uint32_t m_drive_serial_number;
            uint32_t m_ofs_volume_label;
            uint32_t m_ofs_volume_label_unicode;
            bool n_ofs_volume_label_unicode;

        public:
            bool _is_null_ofs_volume_label_unicode() { ofs_volume_label_unicode(); return n_ofs_volume_label_unicode; };

        private:
            windows_lnk_file_t* m__root;
            windows_lnk_file_t::link_info_t::volume_id_spec_t* m__parent;

        public:
            drive_types_t drive_type() const { return m_drive_type; }
            uint32_t drive_serial_number() const { return m_drive_serial_number; }
            uint32_t ofs_volume_label() const { return m_ofs_volume_label; }
            uint32_t ofs_volume_label_unicode() const { return m_ofs_volume_label_unicode; }
            windows_lnk_file_t* _root() const { return m__root; }
            windows_lnk_file_t::link_info_t::volume_id_spec_t* _parent() const { return m__parent; }
        };

        /**
         * \sa Section 2.3
         */

        class all_t : public kaitai::kstruct {

        public:

            all_t(kaitai::kstream* p__io, windows_lnk_file_t::link_info_t* p__parent = 0, windows_lnk_file_t* p__root = 0);

        private:
            void _read();

        public:
            ~all_t();

        private:
            bool f_volume_id;
            volume_id_spec_t* m_volume_id;
            bool n_volume_id;

        public:
            bool _is_null_volume_id() { volume_id(); return n_volume_id; };

        private:

        public:
            volume_id_spec_t* volume_id();

        private:
            bool f_local_base_path;
            std::string m_local_base_path;
            bool n_local_base_path;

        public:
            bool _is_null_local_base_path() { local_base_path(); return n_local_base_path; };

        private:

        public:
            std::string local_base_path();

        private:
            uint32_t m_len_header;
            header_t* m_header;
            windows_lnk_file_t* m__root;
            windows_lnk_file_t::link_info_t* m__parent;
            std::string m__raw_header;
            kaitai::kstream* m__io__raw_header;

        public:
            uint32_t len_header() const { return m_len_header; }
            header_t* header() const { return m_header; }
            windows_lnk_file_t* _root() const { return m__root; }
            windows_lnk_file_t::link_info_t* _parent() const { return m__parent; }
            std::string _raw_header() const { return m__raw_header; }
            kaitai::kstream* _io__raw_header() const { return m__io__raw_header; }
        };

        /**
         * \sa Section 2.3.1
         */

        class volume_id_spec_t : public kaitai::kstruct {

        public:

            volume_id_spec_t(kaitai::kstream* p__io, windows_lnk_file_t::link_info_t::all_t* p__parent = 0, windows_lnk_file_t* p__root = 0);

        private:
            void _read();

        public:
            ~volume_id_spec_t();

        private:
            uint32_t m_len_all;
            volume_id_body_t* m_body;
            windows_lnk_file_t* m__root;
            windows_lnk_file_t::link_info_t::all_t* m__parent;
            std::string m__raw_body;
            kaitai::kstream* m__io__raw_body;

        public:
            uint32_t len_all() const { return m_len_all; }
            volume_id_body_t* body() const { return m_body; }
            windows_lnk_file_t* _root() const { return m__root; }
            windows_lnk_file_t::link_info_t::all_t* _parent() const { return m__parent; }
            std::string _raw_body() const { return m__raw_body; }
            kaitai::kstream* _io__raw_body() const { return m__io__raw_body; }
        };

        /**
         * \sa Section 2.3
         */

        class link_info_flags_t : public kaitai::kstruct {

        public:

            link_info_flags_t(kaitai::kstream* p__io, windows_lnk_file_t::link_info_t::header_t* p__parent = 0, windows_lnk_file_t* p__root = 0);

        private:
            void _read();

        public:
            ~link_info_flags_t();

        private:
            uint64_t m_reserved1;
            bool m_has_common_net_rel_link;
            bool m_has_volume_id_and_local_base_path;
            uint64_t m_reserved2;
            windows_lnk_file_t* m__root;
            windows_lnk_file_t::link_info_t::header_t* m__parent;

        public:
            uint64_t reserved1() const { return m_reserved1; }
            bool has_common_net_rel_link() const { return m_has_common_net_rel_link; }
            bool has_volume_id_and_local_base_path() const { return m_has_volume_id_and_local_base_path; }
            uint64_t reserved2() const { return m_reserved2; }
            windows_lnk_file_t* _root() const { return m__root; }
            windows_lnk_file_t::link_info_t::header_t* _parent() const { return m__parent; }
        };

        /**
         * \sa Section 2.3
         */

        class header_t : public kaitai::kstruct {

        public:

            header_t(kaitai::kstream* p__io, windows_lnk_file_t::link_info_t::all_t* p__parent = 0, windows_lnk_file_t* p__root = 0);

        private:
            void _read();

        public:
            ~header_t();

        private:
            link_info_flags_t* m_flags;
            uint32_t m_ofs_volume_id;
            uint32_t m_ofs_local_base_path;
            uint32_t m_ofs_common_net_rel_link;
            uint32_t m_ofs_common_path_suffix;
            uint32_t m_ofs_local_base_path_unicode;
            bool n_ofs_local_base_path_unicode;

        public:
            bool _is_null_ofs_local_base_path_unicode() { ofs_local_base_path_unicode(); return n_ofs_local_base_path_unicode; };

        private:
            uint32_t m_ofs_common_path_suffix_unicode;
            bool n_ofs_common_path_suffix_unicode;

        public:
            bool _is_null_ofs_common_path_suffix_unicode() { ofs_common_path_suffix_unicode(); return n_ofs_common_path_suffix_unicode; };

        private:
            windows_lnk_file_t* m__root;
            windows_lnk_file_t::link_info_t::all_t* m__parent;

        public:
            link_info_flags_t* flags() const { return m_flags; }
            uint32_t ofs_volume_id() const { return m_ofs_volume_id; }
            uint32_t ofs_local_base_path() const { return m_ofs_local_base_path; }
            uint32_t ofs_common_net_rel_link() const { return m_ofs_common_net_rel_link; }
            uint32_t ofs_common_path_suffix() const { return m_ofs_common_path_suffix; }
            uint32_t ofs_local_base_path_unicode() const { return m_ofs_local_base_path_unicode; }
            uint32_t ofs_common_path_suffix_unicode() const { return m_ofs_common_path_suffix_unicode; }
            windows_lnk_file_t* _root() const { return m__root; }
            windows_lnk_file_t::link_info_t::all_t* _parent() const { return m__parent; }
        };

    private:
        uint32_t m_len_all;
        all_t* m_all;
        windows_lnk_file_t* m__root;
        windows_lnk_file_t* m__parent;
        std::string m__raw_all;
        kaitai::kstream* m__io__raw_all;

    public:
        uint32_t len_all() const { return m_len_all; }
        all_t* all() const { return m_all; }
        windows_lnk_file_t* _root() const { return m__root; }
        windows_lnk_file_t* _parent() const { return m__parent; }
        std::string _raw_all() const { return m__raw_all; }
        kaitai::kstream* _io__raw_all() const { return m__io__raw_all; }
    };

    /**
     * \sa Section 2.1.1
     */

    class link_flags_t : public kaitai::kstruct {

    public:

        link_flags_t(kaitai::kstream* p__io, windows_lnk_file_t::file_header_t* p__parent = 0, windows_lnk_file_t* p__root = 0);

    private:
        void _read();

    public:
        ~link_flags_t();

    private:
        bool m_is_unicode;
        bool m_has_icon_location;
        bool m_has_arguments;
        bool m_has_work_dir;
        bool m_has_rel_path;
        bool m_has_name;
        bool m_has_link_info;
        bool m_has_link_target_id_list;
        uint64_t m__unnamed8;
        uint64_t m_reserved;
        bool m_keep_local_id_list_for_unc_target;
        uint64_t m__unnamed11;
        windows_lnk_file_t* m__root;
        windows_lnk_file_t::file_header_t* m__parent;

    public:
        bool is_unicode() const { return m_is_unicode; }
        bool has_icon_location() const { return m_has_icon_location; }
        bool has_arguments() const { return m_has_arguments; }
        bool has_work_dir() const { return m_has_work_dir; }
        bool has_rel_path() const { return m_has_rel_path; }
        bool has_name() const { return m_has_name; }
        bool has_link_info() const { return m_has_link_info; }
        bool has_link_target_id_list() const { return m_has_link_target_id_list; }
        uint64_t _unnamed8() const { return m__unnamed8; }
        uint64_t reserved() const { return m_reserved; }
        bool keep_local_id_list_for_unc_target() const { return m_keep_local_id_list_for_unc_target; }
        uint64_t _unnamed11() const { return m__unnamed11; }
        windows_lnk_file_t* _root() const { return m__root; }
        windows_lnk_file_t::file_header_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Section 2.1
     */

    class file_header_t : public kaitai::kstruct {

    public:

        file_header_t(kaitai::kstream* p__io, windows_lnk_file_t* p__parent = 0, windows_lnk_file_t* p__root = 0);

    private:
        void _read();

    public:
        ~file_header_t();

    private:
        std::string m_len_header;
        std::string m_link_clsid;
        link_flags_t* m_flags;
        uint32_t m_file_attrs;
        uint64_t m_time_creation;
        uint64_t m_time_access;
        uint64_t m_time_write;
        uint32_t m_target_file_size;
        int32_t m_icon_index;
        window_state_t m_show_command;
        uint16_t m_hotkey;
        std::string m_reserved;
        windows_lnk_file_t* m__root;
        windows_lnk_file_t* m__parent;
        std::string m__raw_flags;
        kaitai::kstream* m__io__raw_flags;

    public:

        /**
         * Technically, a size of the header, but in reality, it's
         * fixed by standard.
         */
        std::string len_header() const { return m_len_header; }

        /**
         * 16-byte class identified (CLSID), reserved for Windows shell
         * link files.
         */
        std::string link_clsid() const { return m_link_clsid; }
        link_flags_t* flags() const { return m_flags; }
        uint32_t file_attrs() const { return m_file_attrs; }
        uint64_t time_creation() const { return m_time_creation; }
        uint64_t time_access() const { return m_time_access; }
        uint64_t time_write() const { return m_time_write; }

        /**
         * Lower 32 bits of the size of the file that this link targets
         */
        uint32_t target_file_size() const { return m_target_file_size; }

        /**
         * Index of an icon to use from target file
         */
        int32_t icon_index() const { return m_icon_index; }

        /**
         * Window state to set after the launch of target executable
         */
        window_state_t show_command() const { return m_show_command; }
        uint16_t hotkey() const { return m_hotkey; }
        std::string reserved() const { return m_reserved; }
        windows_lnk_file_t* _root() const { return m__root; }
        windows_lnk_file_t* _parent() const { return m__parent; }
        std::string _raw_flags() const { return m__raw_flags; }
        kaitai::kstream* _io__raw_flags() const { return m__io__raw_flags; }
    };

private:
    file_header_t* m_header;
    link_target_id_list_t* m_target_id_list;
    bool n_target_id_list;

public:
    bool _is_null_target_id_list() { target_id_list(); return n_target_id_list; };

private:
    link_info_t* m_info;
    bool n_info;

public:
    bool _is_null_info() { info(); return n_info; };

private:
    string_data_t* m_name;
    bool n_name;

public:
    bool _is_null_name() { name(); return n_name; };

private:
    string_data_t* m_rel_path;
    bool n_rel_path;

public:
    bool _is_null_rel_path() { rel_path(); return n_rel_path; };

private:
    string_data_t* m_work_dir;
    bool n_work_dir;

public:
    bool _is_null_work_dir() { work_dir(); return n_work_dir; };

private:
    string_data_t* m_arguments;
    bool n_arguments;

public:
    bool _is_null_arguments() { arguments(); return n_arguments; };

private:
    string_data_t* m_icon_location;
    bool n_icon_location;

public:
    bool _is_null_icon_location() { icon_location(); return n_icon_location; };

private:
    windows_lnk_file_t* m__root;
    kaitai::kstruct* m__parent;

public:
    file_header_t* header() const { return m_header; }
    link_target_id_list_t* target_id_list() const { return m_target_id_list; }
    link_info_t* info() const { return m_info; }
    string_data_t* name() const { return m_name; }
    string_data_t* rel_path() const { return m_rel_path; }
    string_data_t* work_dir() const { return m_work_dir; }
    string_data_t* arguments() const { return m_arguments; }
    string_data_t* icon_location() const { return m_icon_location; }
    windows_lnk_file_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // WINDOWS_LNK_FILE_H_
