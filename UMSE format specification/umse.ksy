meta:
  id: umse
  file-extension: umse
  endian: le

seq:
  - id: umse_header
    type: header
  - id: decryption_table
    type: decryption_table
    repeat: expr
    repeat-expr: umse_header.num_records_dec_table
  - id: entry
    type: entry
    repeat: expr
    repeat-expr: umse_header.num_file_entries
  - id: file_properties
    type: file_properties
  - id: authentication_header
    type: authentication_header

types:
  header:
    seq:
      - id: magic
        contents: UMSE
        doc: "Magic of: Universal Malware Sample Encryption"
      - id: version
        type: str
        encoding: UTF-8
        size: 4
        doc: "Magic of: Universal Malware Sample Encryption"
      - id: num_records_dec_table
        type: u4
        doc: "Number of Records in Decryption Table"
      - id: num_file_entries
        type: u4
        doc: "Number of file entries or encrypted byte chunks"
      - id: author_name_length
        type: u4
        doc: "Author name length"
      - id: author_name
        type: str
        size: author_name_length
        encoding: UTF-8
        doc: "Author name"
  decryption_table:
    seq:
      - id: level_of_confidentiality
        type: u1
      - id: aes_wrapped
        type: u1
        repeat: expr
        repeat-expr: 256
  entry:
    seq:
      - id: size
        type: u4
      - id: level_of_confidentiality
        type: u1
      - id: encrypted_message
        type: u1
        repeat: expr
        repeat-expr: size
      - id: num_metadata
        type: u4
      - id: entry_metadata
        type: entry_metadata
        repeat: expr
        repeat-expr: num_metadata
        if: num_metadata > 0
  entry_metadata:
    seq:
      - id: tag
        type: u1
        repeat: expr
        repeat-expr: 8
      - id: length
        type: u4
      - id: value
        type: u1
        repeat: expr
        repeat-expr: length
  file_properties:
    seq:
      - id: level_of_confidentiality
        type: u1
      - id: hash_value
        type: u1
        repeat: expr
        repeat-expr: 32
      - id: num_metadata
        type: u4
      - id: file_metadata
        type: file_metadata
        repeat: expr
        repeat-expr: num_metadata
        if: num_metadata > 0
  file_metadata:
    seq:
      - id: tag
        type: u1
        repeat: expr
        repeat-expr: 8
      - id: length
        type: u4
      - id: value
        type: u1
        repeat: expr
        repeat-expr: length
  authentication_header:
    seq:
      - id: length
        type: u4
        doc: "HMAC length"
      - id: hmac
        type: u1
        repeat: expr
        repeat-expr: length
        doc: "HMAC"
  rsa_private_key:
    seq:
      - id: length
        type: u4
        if: not _io.eof
        doc: "RSA private key length"
      - id: rsa_private_key
        type: u1
        repeat: expr
        repeat-expr: length
        if: not _io.eof
        doc: "RSA private key"