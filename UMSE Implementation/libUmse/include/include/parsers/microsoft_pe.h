#ifndef MICROSOFT_PE_H_
#define MICROSOFT_PE_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"

#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 7000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.7 or later is required"
#endif

/**
 * \sa Source
 */

class microsoft_pe_t : public kaitai::kstruct {

public:
    class optional_header_windows_t;
    class optional_header_data_dirs_t;
    class data_dir_t;
    class coff_symbol_t;
    class optional_header_t;
    class section_t;
    class mz_placeholder_t;
    class optional_header_std_t;
    class coff_header_t;
    class annoyingstring_t;

    enum pe_format_t {
        PE_FORMAT_ROM_IMAGE = 263,
        PE_FORMAT_PE32 = 267,
        PE_FORMAT_PE32_PLUS = 523
    };

    microsoft_pe_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, microsoft_pe_t* p__root = 0);

private:
    void _read();

public:
    ~microsoft_pe_t();

    class optional_header_windows_t : public kaitai::kstruct {

    public:

        enum subsystem_enum_t {
            SUBSYSTEM_ENUM_UNKNOWN = 0,
            SUBSYSTEM_ENUM_NATIVE = 1,
            SUBSYSTEM_ENUM_WINDOWS_GUI = 2,
            SUBSYSTEM_ENUM_WINDOWS_CUI = 3,
            SUBSYSTEM_ENUM_POSIX_CUI = 7,
            SUBSYSTEM_ENUM_WINDOWS_CE_GUI = 9,
            SUBSYSTEM_ENUM_EFI_APPLICATION = 10,
            SUBSYSTEM_ENUM_EFI_BOOT_SERVICE_DRIVER = 11,
            SUBSYSTEM_ENUM_EFI_RUNTIME_DRIVER = 12,
            SUBSYSTEM_ENUM_EFI_ROM = 13,
            SUBSYSTEM_ENUM_XBOX = 14
        };

        optional_header_windows_t(kaitai::kstream* p__io, microsoft_pe_t::optional_header_t* p__parent = 0, microsoft_pe_t* p__root = 0);

    private:
        void _read();

    public:
        ~optional_header_windows_t();

    private:
        uint32_t m_image_base_32;
        bool n_image_base_32;

    public:
        bool _is_null_image_base_32() { image_base_32(); return n_image_base_32; };

    private:
        uint64_t m_image_base_64;
        bool n_image_base_64;

    public:
        bool _is_null_image_base_64() { image_base_64(); return n_image_base_64; };

    private:
        uint32_t m_section_alignment;
        uint32_t m_file_alignment;
        uint16_t m_major_operating_system_version;
        uint16_t m_minor_operating_system_version;
        uint16_t m_major_image_version;
        uint16_t m_minor_image_version;
        uint16_t m_major_subsystem_version;
        uint16_t m_minor_subsystem_version;
        uint32_t m_win32_version_value;
        uint32_t m_size_of_image;
        uint32_t m_size_of_headers;
        uint32_t m_check_sum;
        subsystem_enum_t m_subsystem;
        uint16_t m_dll_characteristics;
        uint32_t m_size_of_stack_reserve_32;
        bool n_size_of_stack_reserve_32;

    public:
        bool _is_null_size_of_stack_reserve_32() { size_of_stack_reserve_32(); return n_size_of_stack_reserve_32; };

    private:
        uint64_t m_size_of_stack_reserve_64;
        bool n_size_of_stack_reserve_64;

    public:
        bool _is_null_size_of_stack_reserve_64() { size_of_stack_reserve_64(); return n_size_of_stack_reserve_64; };

    private:
        uint32_t m_size_of_stack_commit_32;
        bool n_size_of_stack_commit_32;

    public:
        bool _is_null_size_of_stack_commit_32() { size_of_stack_commit_32(); return n_size_of_stack_commit_32; };

    private:
        uint64_t m_size_of_stack_commit_64;
        bool n_size_of_stack_commit_64;

    public:
        bool _is_null_size_of_stack_commit_64() { size_of_stack_commit_64(); return n_size_of_stack_commit_64; };

    private:
        uint32_t m_size_of_heap_reserve_32;
        bool n_size_of_heap_reserve_32;

    public:
        bool _is_null_size_of_heap_reserve_32() { size_of_heap_reserve_32(); return n_size_of_heap_reserve_32; };

    private:
        uint64_t m_size_of_heap_reserve_64;
        bool n_size_of_heap_reserve_64;

    public:
        bool _is_null_size_of_heap_reserve_64() { size_of_heap_reserve_64(); return n_size_of_heap_reserve_64; };

    private:
        uint32_t m_size_of_heap_commit_32;
        bool n_size_of_heap_commit_32;

    public:
        bool _is_null_size_of_heap_commit_32() { size_of_heap_commit_32(); return n_size_of_heap_commit_32; };

    private:
        uint64_t m_size_of_heap_commit_64;
        bool n_size_of_heap_commit_64;

    public:
        bool _is_null_size_of_heap_commit_64() { size_of_heap_commit_64(); return n_size_of_heap_commit_64; };

    private:
        uint32_t m_loader_flags;
        uint32_t m_number_of_rva_and_sizes;
        microsoft_pe_t* m__root;
        microsoft_pe_t::optional_header_t* m__parent;

    public:
        uint32_t image_base_32() const { return m_image_base_32; }
        uint64_t image_base_64() const { return m_image_base_64; }
        uint32_t section_alignment() const { return m_section_alignment; }
        uint32_t file_alignment() const { return m_file_alignment; }
        uint16_t major_operating_system_version() const { return m_major_operating_system_version; }
        uint16_t minor_operating_system_version() const { return m_minor_operating_system_version; }
        uint16_t major_image_version() const { return m_major_image_version; }
        uint16_t minor_image_version() const { return m_minor_image_version; }
        uint16_t major_subsystem_version() const { return m_major_subsystem_version; }
        uint16_t minor_subsystem_version() const { return m_minor_subsystem_version; }
        uint32_t win32_version_value() const { return m_win32_version_value; }
        uint32_t size_of_image() const { return m_size_of_image; }
        uint32_t size_of_headers() const { return m_size_of_headers; }
        uint32_t check_sum() const { return m_check_sum; }
        subsystem_enum_t subsystem() const { return m_subsystem; }
        uint16_t dll_characteristics() const { return m_dll_characteristics; }
        uint32_t size_of_stack_reserve_32() const { return m_size_of_stack_reserve_32; }
        uint64_t size_of_stack_reserve_64() const { return m_size_of_stack_reserve_64; }
        uint32_t size_of_stack_commit_32() const { return m_size_of_stack_commit_32; }
        uint64_t size_of_stack_commit_64() const { return m_size_of_stack_commit_64; }
        uint32_t size_of_heap_reserve_32() const { return m_size_of_heap_reserve_32; }
        uint64_t size_of_heap_reserve_64() const { return m_size_of_heap_reserve_64; }
        uint32_t size_of_heap_commit_32() const { return m_size_of_heap_commit_32; }
        uint64_t size_of_heap_commit_64() const { return m_size_of_heap_commit_64; }
        uint32_t loader_flags() const { return m_loader_flags; }
        uint32_t number_of_rva_and_sizes() const { return m_number_of_rva_and_sizes; }
        microsoft_pe_t* _root() const { return m__root; }
        microsoft_pe_t::optional_header_t* _parent() const { return m__parent; }
    };

    class optional_header_data_dirs_t : public kaitai::kstruct {

    public:

        optional_header_data_dirs_t(kaitai::kstream* p__io, microsoft_pe_t::optional_header_t* p__parent = 0, microsoft_pe_t* p__root = 0);

    private:
        void _read();

    public:
        ~optional_header_data_dirs_t();

    private:
        data_dir_t* m_export_table;
        data_dir_t* m_import_table;
        data_dir_t* m_resource_table;
        data_dir_t* m_exception_table;
        data_dir_t* m_certificate_table;
        data_dir_t* m_base_relocation_table;
        data_dir_t* m_debug;
        data_dir_t* m_architecture;
        data_dir_t* m_global_ptr;
        data_dir_t* m_tls_table;
        data_dir_t* m_load_config_table;
        data_dir_t* m_bound_import;
        data_dir_t* m_iat;
        data_dir_t* m_delay_import_descriptor;
        data_dir_t* m_clr_runtime_header;
        microsoft_pe_t* m__root;
        microsoft_pe_t::optional_header_t* m__parent;

    public:
        data_dir_t* export_table() const { return m_export_table; }
        data_dir_t* import_table() const { return m_import_table; }
        data_dir_t* resource_table() const { return m_resource_table; }
        data_dir_t* exception_table() const { return m_exception_table; }
        data_dir_t* certificate_table() const { return m_certificate_table; }
        data_dir_t* base_relocation_table() const { return m_base_relocation_table; }
        data_dir_t* debug() const { return m_debug; }
        data_dir_t* architecture() const { return m_architecture; }
        data_dir_t* global_ptr() const { return m_global_ptr; }
        data_dir_t* tls_table() const { return m_tls_table; }
        data_dir_t* load_config_table() const { return m_load_config_table; }
        data_dir_t* bound_import() const { return m_bound_import; }
        data_dir_t* iat() const { return m_iat; }
        data_dir_t* delay_import_descriptor() const { return m_delay_import_descriptor; }
        data_dir_t* clr_runtime_header() const { return m_clr_runtime_header; }
        microsoft_pe_t* _root() const { return m__root; }
        microsoft_pe_t::optional_header_t* _parent() const { return m__parent; }
    };

    class data_dir_t : public kaitai::kstruct {

    public:

        data_dir_t(kaitai::kstream* p__io, microsoft_pe_t::optional_header_data_dirs_t* p__parent = 0, microsoft_pe_t* p__root = 0);

    private:
        void _read();

    public:
        ~data_dir_t();

    private:
        uint32_t m_virtual_address;
        uint32_t m_size;
        microsoft_pe_t* m__root;
        microsoft_pe_t::optional_header_data_dirs_t* m__parent;

    public:
        uint32_t virtual_address() const { return m_virtual_address; }
        uint32_t size() const { return m_size; }
        microsoft_pe_t* _root() const { return m__root; }
        microsoft_pe_t::optional_header_data_dirs_t* _parent() const { return m__parent; }
    };

    class coff_symbol_t : public kaitai::kstruct {

    public:

        coff_symbol_t(kaitai::kstream* p__io, microsoft_pe_t::coff_header_t* p__parent = 0, microsoft_pe_t* p__root = 0);

    private:
        void _read();

    public:
        ~coff_symbol_t();

    private:
        bool f_section;
        section_t* m_section;

    public:
        section_t* section();

    private:
        bool f_data;
        std::string m_data;

    public:
        std::string data();

    private:
        annoyingstring_t* m_name_annoying;
        uint32_t m_value;
        uint16_t m_section_number;
        uint16_t m_type;
        uint8_t m_storage_class;
        uint8_t m_number_of_aux_symbols;
        microsoft_pe_t* m__root;
        microsoft_pe_t::coff_header_t* m__parent;
        std::string m__raw_name_annoying;
        kaitai::kstream* m__io__raw_name_annoying;

    public:
        annoyingstring_t* name_annoying() const { return m_name_annoying; }
        uint32_t value() const { return m_value; }
        uint16_t section_number() const { return m_section_number; }
        uint16_t type() const { return m_type; }
        uint8_t storage_class() const { return m_storage_class; }
        uint8_t number_of_aux_symbols() const { return m_number_of_aux_symbols; }
        microsoft_pe_t* _root() const { return m__root; }
        microsoft_pe_t::coff_header_t* _parent() const { return m__parent; }
        std::string _raw_name_annoying() const { return m__raw_name_annoying; }
        kaitai::kstream* _io__raw_name_annoying() const { return m__io__raw_name_annoying; }
    };

    class optional_header_t : public kaitai::kstruct {

    public:

        optional_header_t(kaitai::kstream* p__io, microsoft_pe_t* p__parent = 0, microsoft_pe_t* p__root = 0);

    private:
        void _read();

    public:
        ~optional_header_t();

    private:
        optional_header_std_t* m_std;
        optional_header_windows_t* m_windows;
        optional_header_data_dirs_t* m_data_dirs;
        microsoft_pe_t* m__root;
        microsoft_pe_t* m__parent;

    public:
        optional_header_std_t* std() const { return m_std; }
        optional_header_windows_t* windows() const { return m_windows; }
        optional_header_data_dirs_t* data_dirs() const { return m_data_dirs; }
        microsoft_pe_t* _root() const { return m__root; }
        microsoft_pe_t* _parent() const { return m__parent; }
    };

    class section_t : public kaitai::kstruct {

    public:

        section_t(kaitai::kstream* p__io, microsoft_pe_t* p__parent = 0, microsoft_pe_t* p__root = 0);

    private:
        void _read();

    public:
        ~section_t();

    private:
        bool f_body;
        std::string m_body;

    public:
        std::string body();

    private:
        std::string m_name;
        uint32_t m_virtual_size;
        uint32_t m_virtual_address;
        uint32_t m_size_of_raw_data;
        uint32_t m_pointer_to_raw_data;
        uint32_t m_pointer_to_relocations;
        uint32_t m_pointer_to_linenumbers;
        uint16_t m_number_of_relocations;
        uint16_t m_number_of_linenumbers;
        uint32_t m_characteristics;
        microsoft_pe_t* m__root;
        microsoft_pe_t* m__parent;

    public:
        std::string name() const { return m_name; }
        uint32_t virtual_size() const { return m_virtual_size; }
        uint32_t virtual_address() const { return m_virtual_address; }
        uint32_t size_of_raw_data() const { return m_size_of_raw_data; }
        uint32_t pointer_to_raw_data() const { return m_pointer_to_raw_data; }
        uint32_t pointer_to_relocations() const { return m_pointer_to_relocations; }
        uint32_t pointer_to_linenumbers() const { return m_pointer_to_linenumbers; }
        uint16_t number_of_relocations() const { return m_number_of_relocations; }
        uint16_t number_of_linenumbers() const { return m_number_of_linenumbers; }
        uint32_t characteristics() const { return m_characteristics; }
        microsoft_pe_t* _root() const { return m__root; }
        microsoft_pe_t* _parent() const { return m__parent; }
    };

    class mz_placeholder_t : public kaitai::kstruct {

    public:

        mz_placeholder_t(kaitai::kstream* p__io, microsoft_pe_t* p__parent = 0, microsoft_pe_t* p__root = 0);

    private:
        void _read();

    public:
        ~mz_placeholder_t();

    private:
        std::string m_magic;
        std::string m_data1;
        uint32_t m_header_size;
        microsoft_pe_t* m__root;
        microsoft_pe_t* m__parent;

    public:
        std::string magic() const { return m_magic; }
        std::string data1() const { return m_data1; }
        uint32_t header_size() const { return m_header_size; }
        microsoft_pe_t* _root() const { return m__root; }
        microsoft_pe_t* _parent() const { return m__parent; }
    };

    class optional_header_std_t : public kaitai::kstruct {

    public:

        optional_header_std_t(kaitai::kstream* p__io, microsoft_pe_t::optional_header_t* p__parent = 0, microsoft_pe_t* p__root = 0);

    private:
        void _read();

    public:
        ~optional_header_std_t();

    private:
        pe_format_t m_format;
        uint8_t m_major_linker_version;
        uint8_t m_minor_linker_version;
        uint32_t m_size_of_code;
        uint32_t m_size_of_initialized_data;
        uint32_t m_size_of_uninitialized_data;
        uint32_t m_address_of_entry_point;
        uint32_t m_base_of_code;
        uint32_t m_base_of_data;
        bool n_base_of_data;

    public:
        bool _is_null_base_of_data() { base_of_data(); return n_base_of_data; };

    private:
        microsoft_pe_t* m__root;
        microsoft_pe_t::optional_header_t* m__parent;

    public:
        pe_format_t format() const { return m_format; }
        uint8_t major_linker_version() const { return m_major_linker_version; }
        uint8_t minor_linker_version() const { return m_minor_linker_version; }
        uint32_t size_of_code() const { return m_size_of_code; }
        uint32_t size_of_initialized_data() const { return m_size_of_initialized_data; }
        uint32_t size_of_uninitialized_data() const { return m_size_of_uninitialized_data; }
        uint32_t address_of_entry_point() const { return m_address_of_entry_point; }
        uint32_t base_of_code() const { return m_base_of_code; }
        uint32_t base_of_data() const { return m_base_of_data; }
        microsoft_pe_t* _root() const { return m__root; }
        microsoft_pe_t::optional_header_t* _parent() const { return m__parent; }
    };

    /**
     * \sa 3.3. COFF File Header (Object and Image)
     */

    class coff_header_t : public kaitai::kstruct {

    public:

        enum machine_type_t {
            MACHINE_TYPE_UNKNOWN = 0,
            MACHINE_TYPE_I386 = 332,
            MACHINE_TYPE_R4000 = 358,
            MACHINE_TYPE_WCEMIPSV2 = 361,
            MACHINE_TYPE_SH3 = 418,
            MACHINE_TYPE_SH3DSP = 419,
            MACHINE_TYPE_SH4 = 422,
            MACHINE_TYPE_SH5 = 424,
            MACHINE_TYPE_ARM = 448,
            MACHINE_TYPE_THUMB = 450,
            MACHINE_TYPE_ARMNT = 452,
            MACHINE_TYPE_AM33 = 467,
            MACHINE_TYPE_POWERPC = 496,
            MACHINE_TYPE_POWERPCFP = 497,
            MACHINE_TYPE_IA64 = 512,
            MACHINE_TYPE_MIPS16 = 614,
            MACHINE_TYPE_MIPSFPU = 870,
            MACHINE_TYPE_MIPSFPU16 = 1126,
            MACHINE_TYPE_EBC = 3772,
            MACHINE_TYPE_RISCV32 = 20530,
            MACHINE_TYPE_RISCV64 = 20580,
            MACHINE_TYPE_RISCV128 = 20776,
            MACHINE_TYPE_AMD64 = 34404,
            MACHINE_TYPE_M32R = 36929
        };

        coff_header_t(kaitai::kstream* p__io, microsoft_pe_t* p__parent = 0, microsoft_pe_t* p__root = 0);

    private:
        void _read();

    public:
        ~coff_header_t();

    private:
        bool f_symbol_table_size;
        int32_t m_symbol_table_size;

    public:
        int32_t symbol_table_size();

    private:
        bool f_symbol_name_table_offset;
        int32_t m_symbol_name_table_offset;

    public:
        int32_t symbol_name_table_offset();

    private:
        bool f_symbol_name_table_size;
        uint32_t m_symbol_name_table_size;

    public:
        uint32_t symbol_name_table_size();

    private:
        bool f_symbol_table;
        std::vector<coff_symbol_t*>* m_symbol_table;

    public:
        std::vector<coff_symbol_t*>* symbol_table();

    private:
        machine_type_t m_machine;
        uint16_t m_number_of_sections;
        uint32_t m_time_date_stamp;
        uint32_t m_pointer_to_symbol_table;
        uint32_t m_number_of_symbols;
        uint16_t m_size_of_optional_header;
        uint16_t m_characteristics;
        microsoft_pe_t* m__root;
        microsoft_pe_t* m__parent;

    public:
        machine_type_t machine() const { return m_machine; }
        uint16_t number_of_sections() const { return m_number_of_sections; }
        uint32_t time_date_stamp() const { return m_time_date_stamp; }
        uint32_t pointer_to_symbol_table() const { return m_pointer_to_symbol_table; }
        uint32_t number_of_symbols() const { return m_number_of_symbols; }
        uint16_t size_of_optional_header() const { return m_size_of_optional_header; }
        uint16_t characteristics() const { return m_characteristics; }
        microsoft_pe_t* _root() const { return m__root; }
        microsoft_pe_t* _parent() const { return m__parent; }
    };

    class annoyingstring_t : public kaitai::kstruct {

    public:

        annoyingstring_t(kaitai::kstream* p__io, microsoft_pe_t::coff_symbol_t* p__parent = 0, microsoft_pe_t* p__root = 0);

    private:
        void _read();

    public:
        ~annoyingstring_t();

    private:
        bool f_name_zeroes;
        uint32_t m_name_zeroes;

    public:
        uint32_t name_zeroes();

    private:
        bool f_name_offset;
        uint32_t m_name_offset;

    public:
        uint32_t name_offset();

    private:
        bool f_name_from_short;
        std::string m_name_from_short;

    public:
        std::string name_from_short();

    private:
        microsoft_pe_t* m__root;
        microsoft_pe_t::coff_symbol_t* m__parent;

    public:
        microsoft_pe_t* _root() const { return m__root; }
        microsoft_pe_t::coff_symbol_t* _parent() const { return m__parent; }
    };

private:
    mz_placeholder_t* m_mz1;
    std::string m_mz2;
    std::string m_pe_signature;
    coff_header_t* m_coff_hdr;
    optional_header_t* m_optional_hdr;
    std::vector<section_t*>* m_sections;
    microsoft_pe_t* m__root;
    kaitai::kstruct* m__parent;
    std::string m__raw_optional_hdr;
    kaitai::kstream* m__io__raw_optional_hdr;

public:
    mz_placeholder_t* mz1() const { return m_mz1; }
    std::string mz2() const { return m_mz2; }
    std::string pe_signature() const { return m_pe_signature; }
    coff_header_t* coff_hdr() const { return m_coff_hdr; }
    optional_header_t* optional_hdr() const { return m_optional_hdr; }
    std::vector<section_t*>* sections() const { return m_sections; }
    microsoft_pe_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
    std::string _raw_optional_hdr() const { return m__raw_optional_hdr; }
    kaitai::kstream* _io__raw_optional_hdr() const { return m__io__raw_optional_hdr; }
};

#endif  // MICROSOFT_PE_H_
