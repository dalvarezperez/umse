#ifndef DOS_MZ_H_
#define DOS_MZ_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"

#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 7000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.7 or later is required"
#endif

/**
 * DOS MZ file format is a traditional format for executables in MS-DOS
 * environment. Many modern formats (i.e. Windows PE) still maintain
 * compatibility stub with this format.
 * 
 * As opposed to .com file format (which basically sports one 64K code
 * segment of raw CPU instructions), DOS MZ .exe file format allowed
 * more flexible memory management, loading of larger programs and
 * added support for relocations.
 */

class dos_mz_t : public kaitai::kstruct {

public:
    class mz_header_t;
    class relocation_t;

    dos_mz_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, dos_mz_t* p__root = 0);

private:
    void _read();

public:
    ~dos_mz_t();

    class mz_header_t : public kaitai::kstruct {

    public:

        mz_header_t(kaitai::kstream* p__io, dos_mz_t* p__parent = 0, dos_mz_t* p__root = 0);

    private:
        void _read();

    public:
        ~mz_header_t();

    private:
        std::string m_magic;
        uint16_t m_last_page_extra_bytes;
        uint16_t m_qty_pages;
        uint16_t m_qty_relocations;
        uint16_t m_header_size;
        uint16_t m_min_allocation;
        uint16_t m_max_allocation;
        uint16_t m_initial_ss;
        uint16_t m_initial_sp;
        uint16_t m_checksum;
        uint16_t m_initial_ip;
        uint16_t m_initial_cs;
        uint16_t m_relocations_ofs;
        uint16_t m_overlay_id;
        dos_mz_t* m__root;
        dos_mz_t* m__parent;

    public:
        std::string magic() const { return m_magic; }
        uint16_t last_page_extra_bytes() const { return m_last_page_extra_bytes; }
        uint16_t qty_pages() const { return m_qty_pages; }
        uint16_t qty_relocations() const { return m_qty_relocations; }
        uint16_t header_size() const { return m_header_size; }
        uint16_t min_allocation() const { return m_min_allocation; }
        uint16_t max_allocation() const { return m_max_allocation; }
        uint16_t initial_ss() const { return m_initial_ss; }
        uint16_t initial_sp() const { return m_initial_sp; }
        uint16_t checksum() const { return m_checksum; }
        uint16_t initial_ip() const { return m_initial_ip; }
        uint16_t initial_cs() const { return m_initial_cs; }
        uint16_t relocations_ofs() const { return m_relocations_ofs; }
        uint16_t overlay_id() const { return m_overlay_id; }
        dos_mz_t* _root() const { return m__root; }
        dos_mz_t* _parent() const { return m__parent; }
    };

    class relocation_t : public kaitai::kstruct {

    public:

        relocation_t(kaitai::kstream* p__io, dos_mz_t* p__parent = 0, dos_mz_t* p__root = 0);

    private:
        void _read();

    public:
        ~relocation_t();

    private:
        uint16_t m_ofs;
        uint16_t m_seg;
        dos_mz_t* m__root;
        dos_mz_t* m__parent;

    public:
        uint16_t ofs() const { return m_ofs; }
        uint16_t seg() const { return m_seg; }
        dos_mz_t* _root() const { return m__root; }
        dos_mz_t* _parent() const { return m__parent; }
    };

private:
    mz_header_t* m_hdr;
    std::string m_mz_header2;
    std::vector<relocation_t*>* m_relocations;
    std::string m_body;
    dos_mz_t* m__root;
    kaitai::kstruct* m__parent;

public:
    mz_header_t* hdr() const { return m_hdr; }
    std::string mz_header2() const { return m_mz_header2; }
    std::vector<relocation_t*>* relocations() const { return m_relocations; }
    std::string body() const { return m_body; }
    dos_mz_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // DOS_MZ_H_
