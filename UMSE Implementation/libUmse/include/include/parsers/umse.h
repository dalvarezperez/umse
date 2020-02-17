/**
 *
 * Copyright (c) 2019-2020. The UMSE Authors. All Rights Reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * @file umse.h
 *
 * @brief Kaitai-Struct UMSE structure
 *
 * @author David Alvarez (https://www.linkedin.com/in/davidalvarezperez/)
 * Contact: dalvarezperez87@gmail.com
 *
 */
#ifndef UMSE_H_
#define UMSE_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"

#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 7000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.7 or later is required"
#endif

class umse_t : public kaitai::kstruct {

public:
    class authentication_header_t;
    class entry_t;
    class file_properties_t;
    class rsa_private_key_t;
    class file_metadata_t;
    class header_t;
    class decryption_table_t;
    class entry_metadata_t;

    umse_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, umse_t* p__root = 0);

private:
    void _read();

public:
    ~umse_t();

    class authentication_header_t : public kaitai::kstruct {

    public:

        authentication_header_t(kaitai::kstream* p__io, umse_t* p__parent = 0, umse_t* p__root = 0);

    private:
        void _read();

    public:
        ~authentication_header_t();

    private:
        uint32_t m_length;
        std::vector<uint8_t>* m_hmac;
        umse_t* m__root;
        umse_t* m__parent;

    public:

        /**
         * HMAC length
         */
        uint32_t length() const { return m_length; }

        /**
         * HMAC
         */
        std::vector<uint8_t>* hmac() const { return m_hmac; }
        umse_t* _root() const { return m__root; }
        umse_t* _parent() const { return m__parent; }
    };

    class entry_t : public kaitai::kstruct {

    public:

        entry_t(kaitai::kstream* p__io, umse_t* p__parent = 0, umse_t* p__root = 0);

    private:
        void _read();

    public:
        ~entry_t();

    private:
        uint32_t m_size;
        uint8_t m_level_of_confidentiality;
        std::vector<uint8_t>* m_encrypted_message;
        uint32_t m_num_metadata;
        std::vector<entry_metadata_t*>* m_entry_metadata;
        bool n_entry_metadata;

    public:
        bool _is_null_entry_metadata() { entry_metadata(); return n_entry_metadata; };

    private:
        umse_t* m__root;
        umse_t* m__parent;

    public:
        uint32_t size() const { return m_size; }
        uint8_t level_of_confidentiality() const { return m_level_of_confidentiality; }
        std::vector<uint8_t>* encrypted_message() const { return m_encrypted_message; }
        uint32_t num_metadata() const { return m_num_metadata; }
        std::vector<entry_metadata_t*>* entry_metadata() const { return m_entry_metadata; }
        umse_t* _root() const { return m__root; }
        umse_t* _parent() const { return m__parent; }
    };

    class file_properties_t : public kaitai::kstruct {

    public:

        file_properties_t(kaitai::kstream* p__io, umse_t* p__parent = 0, umse_t* p__root = 0);

    private:
        void _read();

    public:
        ~file_properties_t();

    private:
        uint8_t m_level_of_confidentiality;
        std::vector<uint8_t>* m_hash_value;
        uint32_t m_num_metadata;
        std::vector<file_metadata_t*>* m_file_metadata;
        bool n_file_metadata;

    public:
        bool _is_null_file_metadata() { file_metadata(); return n_file_metadata; };

    private:
        umse_t* m__root;
        umse_t* m__parent;

    public:
        uint8_t level_of_confidentiality() const { return m_level_of_confidentiality; }
        std::vector<uint8_t>* hash_value() const { return m_hash_value; }
        uint32_t num_metadata() const { return m_num_metadata; }
        std::vector<file_metadata_t*>* file_metadata() const { return m_file_metadata; }
        umse_t* _root() const { return m__root; }
        umse_t* _parent() const { return m__parent; }
    };

    class rsa_private_key_t : public kaitai::kstruct {

    public:

        rsa_private_key_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, umse_t* p__root = 0);

    private:
        void _read();

    public:
        ~rsa_private_key_t();

    private:
        uint32_t m_length;
        bool n_length;

    public:
        bool _is_null_length() { length(); return n_length; };

    private:
        std::vector<uint8_t>* m_rsa_private_key;
        bool n_rsa_private_key;

    public:
        bool _is_null_rsa_private_key() { rsa_private_key(); return n_rsa_private_key; };

    private:
        umse_t* m__root;
        kaitai::kstruct* m__parent;

    public:

        /**
         * RSA private key length
         */
        uint32_t length() const { return m_length; }

        /**
         * RSA private key
         */
        std::vector<uint8_t>* rsa_private_key() const { return m_rsa_private_key; }
        umse_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class file_metadata_t : public kaitai::kstruct {

    public:

        file_metadata_t(kaitai::kstream* p__io, umse_t::file_properties_t* p__parent = 0, umse_t* p__root = 0);

    private:
        void _read();

    public:
        ~file_metadata_t();

    private:
        std::vector<uint8_t>* m_tag;
        uint32_t m_length;
        std::vector<uint8_t>* m_value;
        umse_t* m__root;
        umse_t::file_properties_t* m__parent;

    public:
        std::vector<uint8_t>* tag() const { return m_tag; }
        uint32_t length() const { return m_length; }
        std::vector<uint8_t>* value() const { return m_value; }
        umse_t* _root() const { return m__root; }
        umse_t::file_properties_t* _parent() const { return m__parent; }
    };

    class header_t : public kaitai::kstruct {

    public:

        header_t(kaitai::kstream* p__io, umse_t* p__parent = 0, umse_t* p__root = 0);

    private:
        void _read();

    public:
        ~header_t();

    private:
        std::string m_magic;
        std::string m_version;
        uint32_t m_num_records_dec_table;
        uint32_t m_num_file_entries;
        uint32_t m_author_name_length;
        std::string m_author_name;
        umse_t* m__root;
        umse_t* m__parent;

    public:

        /**
         * Magic of: Universal Malware Sample Encryption
         */
        std::string magic() const { return m_magic; }

        /**
         * Magic of: Universal Malware Sample Encryption
         */
        std::string version() const { return m_version; }

        /**
         * Number of Records in Decryption Table
         */
        uint32_t num_records_dec_table() const { return m_num_records_dec_table; }

        /**
         * Number of file entries or encrypted byte chunks
         */
        uint32_t num_file_entries() const { return m_num_file_entries; }

        /**
         * Author name length
         */
        uint32_t author_name_length() const { return m_author_name_length; }

        /**
         * Author name
         */
        std::string author_name() const { return m_author_name; }
        umse_t* _root() const { return m__root; }
        umse_t* _parent() const { return m__parent; }
    };

    class decryption_table_t : public kaitai::kstruct {

    public:

        decryption_table_t(kaitai::kstream* p__io, umse_t* p__parent = 0, umse_t* p__root = 0);

    private:
        void _read();

    public:
        ~decryption_table_t();

    private:
        uint8_t m_level_of_confidentiality;
        std::vector<uint8_t>* m_aes_wrapped;
        umse_t* m__root;
        umse_t* m__parent;

    public:
        uint8_t level_of_confidentiality() const { return m_level_of_confidentiality; }
        std::vector<uint8_t>* aes_wrapped() const { return m_aes_wrapped; }
        umse_t* _root() const { return m__root; }
        umse_t* _parent() const { return m__parent; }
    };

    class entry_metadata_t : public kaitai::kstruct {

    public:

        entry_metadata_t(kaitai::kstream* p__io, umse_t::entry_t* p__parent = 0, umse_t* p__root = 0);

    private:
        void _read();

    public:
        ~entry_metadata_t();

    private:
        std::vector<uint8_t>* m_tag;
        uint32_t m_length;
        std::vector<uint8_t>* m_value;
        umse_t* m__root;
        umse_t::entry_t* m__parent;

    public:
        std::vector<uint8_t>* tag() const { return m_tag; }
        uint32_t length() const { return m_length; }
        std::vector<uint8_t>* value() const { return m_value; }
        umse_t* _root() const { return m__root; }
        umse_t::entry_t* _parent() const { return m__parent; }
    };

private:
    header_t* m_umse_header;
    std::vector<decryption_table_t*>* m_decryption_table;
    std::vector<entry_t*>* m_entry;
    file_properties_t* m_file_properties;
    authentication_header_t* m_authentication_header;
    umse_t* m__root;
    kaitai::kstruct* m__parent;

public:
    header_t* umse_header() const { return m_umse_header; }
    std::vector<decryption_table_t*>* decryption_table() const { return m_decryption_table; }
    std::vector<entry_t*>* entry() const { return m_entry; }
    file_properties_t* file_properties() const { return m_file_properties; }
    authentication_header_t* authentication_header() const { return m_authentication_header; }
    umse_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // UMSE_H_
