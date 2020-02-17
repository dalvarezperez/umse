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

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "umse.h"



umse_t::umse_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, umse_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    _read();
}

void umse_t::_read() {
    m_umse_header = new header_t(m__io, this, m__root);
    int l_decryption_table = umse_header()->num_records_dec_table();
    m_decryption_table = new std::vector<decryption_table_t*>();
    m_decryption_table->reserve(l_decryption_table);
    for (int i = 0; i < l_decryption_table; i++) {
        m_decryption_table->push_back(new decryption_table_t(m__io, this, m__root));
    }
    int l_entry = umse_header()->num_file_entries();
    m_entry = new std::vector<entry_t*>();
    m_entry->reserve(l_entry);
    for (int i = 0; i < l_entry; i++) {
        m_entry->push_back(new entry_t(m__io, this, m__root));
    }
    m_file_properties = new file_properties_t(m__io, this, m__root);
    m_authentication_header = new authentication_header_t(m__io, this, m__root);
}

umse_t::~umse_t() {
    delete m_umse_header;
    for (std::vector<decryption_table_t*>::iterator it = m_decryption_table->begin(); it != m_decryption_table->end(); ++it) {
        delete *it;
    }
    delete m_decryption_table;
    for (std::vector<entry_t*>::iterator it = m_entry->begin(); it != m_entry->end(); ++it) {
        delete *it;
    }
    delete m_entry;
    delete m_file_properties;
    delete m_authentication_header;
}

umse_t::authentication_header_t::authentication_header_t(kaitai::kstream* p__io, umse_t* p__parent, umse_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void umse_t::authentication_header_t::_read() {
    m_length = m__io->read_u4le();
    int l_hmac = length();
    m_hmac = new std::vector<uint8_t>();
    m_hmac->reserve(l_hmac);
    for (int i = 0; i < l_hmac; i++) {
        m_hmac->push_back(m__io->read_u1());
    }
}

umse_t::authentication_header_t::~authentication_header_t() {
    delete m_hmac;
}

umse_t::entry_t::entry_t(kaitai::kstream* p__io, umse_t* p__parent, umse_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void umse_t::entry_t::_read() {
    m_size = m__io->read_u4le();
    m_level_of_confidentiality = m__io->read_u1();
    int l_encrypted_message = size();
    m_encrypted_message = new std::vector<uint8_t>();
    m_encrypted_message->reserve(l_encrypted_message);
    for (int i = 0; i < l_encrypted_message; i++) {
        m_encrypted_message->push_back(m__io->read_u1());
    }
    m_num_metadata = m__io->read_u4le();
    n_entry_metadata = true;
    if (num_metadata() > 0) {
        n_entry_metadata = false;
        int l_entry_metadata = num_metadata();
        m_entry_metadata = new std::vector<entry_metadata_t*>();
        m_entry_metadata->reserve(l_entry_metadata);
        for (int i = 0; i < l_entry_metadata; i++) {
            m_entry_metadata->push_back(new entry_metadata_t(m__io, this, m__root));
        }
    }
}

umse_t::entry_t::~entry_t() {
    delete m_encrypted_message;
    if (!n_entry_metadata) {
        for (std::vector<entry_metadata_t*>::iterator it = m_entry_metadata->begin(); it != m_entry_metadata->end(); ++it) {
            delete *it;
        }
        delete m_entry_metadata;
    }
}

umse_t::file_properties_t::file_properties_t(kaitai::kstream* p__io, umse_t* p__parent, umse_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void umse_t::file_properties_t::_read() {
    m_level_of_confidentiality = m__io->read_u1();
    int l_hash_value = 32;
    m_hash_value = new std::vector<uint8_t>();
    m_hash_value->reserve(l_hash_value);
    for (int i = 0; i < l_hash_value; i++) {
        m_hash_value->push_back(m__io->read_u1());
    }
    m_num_metadata = m__io->read_u4le();
    n_file_metadata = true;
    if (num_metadata() > 0) {
        n_file_metadata = false;
        int l_file_metadata = num_metadata();
        m_file_metadata = new std::vector<file_metadata_t*>();
        m_file_metadata->reserve(l_file_metadata);
        for (int i = 0; i < l_file_metadata; i++) {
            m_file_metadata->push_back(new file_metadata_t(m__io, this, m__root));
        }
    }
}

umse_t::file_properties_t::~file_properties_t() {
    delete m_hash_value;
    if (!n_file_metadata) {
        for (std::vector<file_metadata_t*>::iterator it = m_file_metadata->begin(); it != m_file_metadata->end(); ++it) {
            delete *it;
        }
        delete m_file_metadata;
    }
}

umse_t::rsa_private_key_t::rsa_private_key_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, umse_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void umse_t::rsa_private_key_t::_read() {
    n_length = true;
    if (!(_io()->is_eof())) {
        n_length = false;
        m_length = m__io->read_u4le();
    }
    n_rsa_private_key = true;
    if (!(_io()->is_eof())) {
        n_rsa_private_key = false;
        int l_rsa_private_key = length();
        m_rsa_private_key = new std::vector<uint8_t>();
        m_rsa_private_key->reserve(l_rsa_private_key);
        for (int i = 0; i < l_rsa_private_key; i++) {
            m_rsa_private_key->push_back(m__io->read_u1());
        }
    }
}

umse_t::rsa_private_key_t::~rsa_private_key_t() {
    if (!n_length) {
    }
    if (!n_rsa_private_key) {
        delete m_rsa_private_key;
    }
}

umse_t::file_metadata_t::file_metadata_t(kaitai::kstream* p__io, umse_t::file_properties_t* p__parent, umse_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void umse_t::file_metadata_t::_read() {
    int l_tag = 8;
    m_tag = new std::vector<uint8_t>();
    m_tag->reserve(l_tag);
    for (int i = 0; i < l_tag; i++) {
        m_tag->push_back(m__io->read_u1());
    }
    m_length = m__io->read_u4le();
    int l_value = length();
    m_value = new std::vector<uint8_t>();
    m_value->reserve(l_value);
    for (int i = 0; i < l_value; i++) {
        m_value->push_back(m__io->read_u1());
    }
}

umse_t::file_metadata_t::~file_metadata_t() {
    delete m_tag;
    delete m_value;
}

umse_t::header_t::header_t(kaitai::kstream* p__io, umse_t* p__parent, umse_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void umse_t::header_t::_read() {
    m_magic = m__io->ensure_fixed_contents(std::string("\x55\x4D\x53\x45", 4));
    m_version = kaitai::kstream::bytes_to_str(m__io->read_bytes(4), std::string("UTF-8"));
    m_num_records_dec_table = m__io->read_u4le();
    m_num_file_entries = m__io->read_u4le();
    m_author_name_length = m__io->read_u4le();
    m_author_name = kaitai::kstream::bytes_to_str(m__io->read_bytes(author_name_length()), std::string("UTF-8"));
}

umse_t::header_t::~header_t() {
}

umse_t::decryption_table_t::decryption_table_t(kaitai::kstream* p__io, umse_t* p__parent, umse_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void umse_t::decryption_table_t::_read() {
    m_level_of_confidentiality = m__io->read_u1();
    int l_aes_wrapped = 256;
    m_aes_wrapped = new std::vector<uint8_t>();
    m_aes_wrapped->reserve(l_aes_wrapped);
    for (int i = 0; i < l_aes_wrapped; i++) {
        m_aes_wrapped->push_back(m__io->read_u1());
    }
}

umse_t::decryption_table_t::~decryption_table_t() {
    delete m_aes_wrapped;
}

umse_t::entry_metadata_t::entry_metadata_t(kaitai::kstream* p__io, umse_t::entry_t* p__parent, umse_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    _read();
}

void umse_t::entry_metadata_t::_read() {
    int l_tag = 8;
    m_tag = new std::vector<uint8_t>();
    m_tag->reserve(l_tag);
    for (int i = 0; i < l_tag; i++) {
        m_tag->push_back(m__io->read_u1());
    }
    m_length = m__io->read_u4le();
    int l_value = length();
    m_value = new std::vector<uint8_t>();
    m_value->reserve(l_value);
    for (int i = 0; i < l_value; i++) {
        m_value->push_back(m__io->read_u1());
    }
}

umse_t::entry_metadata_t::~entry_metadata_t() {
    delete m_tag;
    delete m_value;
}
