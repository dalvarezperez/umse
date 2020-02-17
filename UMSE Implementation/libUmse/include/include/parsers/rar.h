#ifndef RAR_H_
#define RAR_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"

#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 7000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.7 or later is required"
#endif

/**
 * RAR is a archive format used by popular proprietary RAR archiver,
 * created by Eugene Roshal. There are two major versions of format
 * (v1.5-4.0 and RAR v5+).
 * 
 * File format essentially consists of a linear sequence of
 * blocks. Each block has fixed header and custom body (that depends on
 * block type), so it's possible to skip block even if one doesn't know
 * how to process a certain block type.
 */

class rar_t : public kaitai::kstruct {

public:
    class block_v5_t;
    class block_t;
    class block_file_header_t;
    class magic_signature_t;
    class dos_time_t;

    enum block_types_t {
        BLOCK_TYPES_MARKER = 114,
        BLOCK_TYPES_ARCHIVE_HEADER = 115,
        BLOCK_TYPES_FILE_HEADER = 116,
        BLOCK_TYPES_OLD_STYLE_COMMENT_HEADER = 117,
        BLOCK_TYPES_OLD_STYLE_AUTHENTICITY_INFO_76 = 118,
        BLOCK_TYPES_OLD_STYLE_SUBBLOCK = 119,
        BLOCK_TYPES_OLD_STYLE_RECOVERY_RECORD = 120,
        BLOCK_TYPES_OLD_STYLE_AUTHENTICITY_INFO_79 = 121,
        BLOCK_TYPES_SUBBLOCK = 122,
        BLOCK_TYPES_TERMINATOR = 123
    };

    enum oses_t {
        OSES_MS_DOS = 0,
        OSES_OS_2 = 1,
        OSES_WINDOWS = 2,
        OSES_UNIX = 3,
        OSES_MAC_OS = 4,
        OSES_BEOS = 5
    };

    enum methods_t {
        METHODS_STORE = 48,
        METHODS_FASTEST = 49,
        METHODS_FAST = 50,
        METHODS_NORMAL = 51,
        METHODS_GOOD = 52,
        METHODS_BEST = 53
    };

    rar_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, rar_t* p__root = 0);

private:
    void _read();

public:
    ~rar_t();

    class block_v5_t : public kaitai::kstruct {

    public:

        block_v5_t(kaitai::kstream* p__io, rar_t* p__parent = 0, rar_t* p__root = 0);

    private:
        void _read();

    public:
        ~block_v5_t();

    private:
        rar_t* m__root;
        rar_t* m__parent;

    public:
        rar_t* _root() const { return m__root; }
        rar_t* _parent() const { return m__parent; }
    };

    /**
     * Basic block that RAR files consist of. There are several block
     * types (see `block_type`), which have different `body` and
     * `add_body`.
     */

    class block_t : public kaitai::kstruct {

    public:

        block_t(kaitai::kstream* p__io, rar_t* p__parent = 0, rar_t* p__root = 0);

    private:
        void _read();

    public:
        ~block_t();

    private:
        bool f_has_add;
        bool m_has_add;

    public:

        /**
         * True if block has additional content attached to it
         */
        bool has_add();

    private:
        bool f_header_size;
        int8_t m_header_size;

    public:
        int8_t header_size();

    private:
        bool f_body_size;
        int32_t m_body_size;

    public:
        int32_t body_size();

    private:
        uint16_t m_crc16;
        block_types_t m_block_type;
        uint16_t m_flags;
        uint16_t m_block_size;
        uint32_t m_add_size;
        bool n_add_size;

    public:
        bool _is_null_add_size() { add_size(); return n_add_size; };

    private:
        block_file_header_t* m_body;
        bool n_body;

    public:
        bool _is_null_body() { body(); return n_body; };

    private:
        std::string m_add_body;
        bool n_add_body;

    public:
        bool _is_null_add_body() { add_body(); return n_add_body; };

    private:
        rar_t* m__root;
        rar_t* m__parent;
        std::string m__raw_body;
        kaitai::kstream* m__io__raw_body;

    public:

        /**
         * CRC16 of whole block or some part of it (depends on block type)
         */
        uint16_t crc16() const { return m_crc16; }
        block_types_t block_type() const { return m_block_type; }
        uint16_t flags() const { return m_flags; }

        /**
         * Size of block (header + body, but without additional content)
         */
        uint16_t block_size() const { return m_block_size; }

        /**
         * Size of additional content in this block
         */
        uint32_t add_size() const { return m_add_size; }
        block_file_header_t* body() const { return m_body; }

        /**
         * Additional content in this block
         */
        std::string add_body() const { return m_add_body; }
        rar_t* _root() const { return m__root; }
        rar_t* _parent() const { return m__parent; }
        std::string _raw_body() const { return m__raw_body; }
        kaitai::kstream* _io__raw_body() const { return m__io__raw_body; }
    };

    class block_file_header_t : public kaitai::kstruct {

    public:

        block_file_header_t(kaitai::kstream* p__io, rar_t::block_t* p__parent = 0, rar_t* p__root = 0);

    private:
        void _read();

    public:
        ~block_file_header_t();

    private:
        uint32_t m_low_unp_size;
        oses_t m_host_os;
        uint32_t m_file_crc32;
        dos_time_t* m_file_time;
        uint8_t m_rar_version;
        methods_t m_method;
        uint16_t m_name_size;
        uint32_t m_attr;
        uint32_t m_high_pack_size;
        bool n_high_pack_size;

    public:
        bool _is_null_high_pack_size() { high_pack_size(); return n_high_pack_size; };

    private:
        std::string m_file_name;
        uint64_t m_salt;
        bool n_salt;

    public:
        bool _is_null_salt() { salt(); return n_salt; };

    private:
        rar_t* m__root;
        rar_t::block_t* m__parent;

    public:

        /**
         * Uncompressed file size (lower 32 bits, if 64-bit header flag is present)
         */
        uint32_t low_unp_size() const { return m_low_unp_size; }

        /**
         * Operating system used for archiving
         */
        oses_t host_os() const { return m_host_os; }
        uint32_t file_crc32() const { return m_file_crc32; }

        /**
         * Date and time in standard MS DOS format
         */
        dos_time_t* file_time() const { return m_file_time; }

        /**
         * RAR version needed to extract file (Version number is encoded as 10 * Major version + minor version.)
         */
        uint8_t rar_version() const { return m_rar_version; }

        /**
         * Compression method
         */
        methods_t method() const { return m_method; }

        /**
         * File name size
         */
        uint16_t name_size() const { return m_name_size; }

        /**
         * File attributes
         */
        uint32_t attr() const { return m_attr; }

        /**
         * Compressed file size, high 32 bits, only if 64-bit header flag is present
         */
        uint32_t high_pack_size() const { return m_high_pack_size; }
        std::string file_name() const { return m_file_name; }
        uint64_t salt() const { return m_salt; }
        rar_t* _root() const { return m__root; }
        rar_t::block_t* _parent() const { return m__parent; }
    };

    /**
     * RAR uses either 7-byte magic for RAR versions 1.5 to 4.0, and
     * 8-byte magic (and pretty different block format) for v5+. This
     * type would parse and validate both versions of signature. Note
     * that actually this signature is a valid RAR "block": in theory,
     * one can omit signature reading at all, and read this normally,
     * as a block, if exact RAR version is known (and thus it's
     * possible to choose correct block format).
     */

    class magic_signature_t : public kaitai::kstruct {

    public:

        magic_signature_t(kaitai::kstream* p__io, rar_t* p__parent = 0, rar_t* p__root = 0);

    private:
        void _read();

    public:
        ~magic_signature_t();

    private:
        std::string m_magic1;
        uint8_t m_version;
        std::string m_magic3;
        bool n_magic3;

    public:
        bool _is_null_magic3() { magic3(); return n_magic3; };

    private:
        rar_t* m__root;
        rar_t* m__parent;

    public:

        /**
         * Fixed part of file's magic signature that doesn't change with RAR version
         */
        std::string magic1() const { return m_magic1; }

        /**
         * Variable part of magic signature: 0 means old (RAR 1.5-4.0)
         * format, 1 means new (RAR 5+) format
         */
        uint8_t version() const { return m_version; }

        /**
         * New format (RAR 5+) magic contains extra byte
         */
        std::string magic3() const { return m_magic3; }
        rar_t* _root() const { return m__root; }
        rar_t* _parent() const { return m__parent; }
    };

    class dos_time_t : public kaitai::kstruct {

    public:

        dos_time_t(kaitai::kstream* p__io, rar_t::block_file_header_t* p__parent = 0, rar_t* p__root = 0);

    private:
        void _read();

    public:
        ~dos_time_t();

    private:
        bool f_month;
        int32_t m_month;

    public:
        int32_t month();

    private:
        bool f_seconds;
        int32_t m_seconds;

    public:
        int32_t seconds();

    private:
        bool f_year;
        int32_t m_year;

    public:
        int32_t year();

    private:
        bool f_minutes;
        int32_t m_minutes;

    public:
        int32_t minutes();

    private:
        bool f_day;
        int32_t m_day;

    public:
        int32_t day();

    private:
        bool f_hours;
        int32_t m_hours;

    public:
        int32_t hours();

    private:
        uint16_t m_time;
        uint16_t m_date;
        rar_t* m__root;
        rar_t::block_file_header_t* m__parent;

    public:
        uint16_t time() const { return m_time; }
        uint16_t date() const { return m_date; }
        rar_t* _root() const { return m__root; }
        rar_t::block_file_header_t* _parent() const { return m__parent; }
    };

private:
    magic_signature_t* m_magic;
    std::vector<kaitai::kstruct*>* m_blocks;
    bool n_blocks;

public:
    bool _is_null_blocks() { blocks(); return n_blocks; };

private:
    rar_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * File format signature to validate that it is indeed a RAR archive
     */
    magic_signature_t* magic() const { return m_magic; }

    /**
     * Sequence of blocks that constitute the RAR file
     */
    std::vector<kaitai::kstruct*>* blocks() const { return m_blocks; }
    rar_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // RAR_H_
