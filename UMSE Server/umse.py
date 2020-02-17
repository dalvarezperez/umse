# This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

from pkg_resources import parse_version
from kaitaistruct import __version__ as ks_version, KaitaiStruct, KaitaiStream, BytesIO


if parse_version(ks_version) < parse_version('0.7'):
    raise Exception("Incompatible Kaitai Struct Python API: 0.7 or later is required, but you have %s" % (ks_version))

class Umse(KaitaiStruct):
    def __init__(self, _io, _parent=None, _root=None):
        self._io = _io
        self._parent = _parent
        self._root = _root if _root else self
        self._read()

    def _read(self):
        self.umse_header = self._root.Header(self._io, self, self._root)
        self.decryption_table = [None] * (self.umse_header.num_records_dec_table)
        for i in range(self.umse_header.num_records_dec_table):
            self.decryption_table[i] = self._root.DecryptionTable(self._io, self, self._root)

        self.entry = [None] * (self.umse_header.num_file_entries)
        for i in range(self.umse_header.num_file_entries):
            self.entry[i] = self._root.Entry(self._io, self, self._root)

        self.file_properties = self._root.FileProperties(self._io, self, self._root)
        self.authentication_header = self._root.AuthenticationHeader(self._io, self, self._root)

    class AuthenticationHeader(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.length = self._io.read_u4le()
            self.hmac = [None] * (self.length)
            for i in range(self.length):
                self.hmac[i] = self._io.read_u1()



    class Entry(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.size = self._io.read_u4le()
            self.level_of_confidentiality = self._io.read_u1()
            self.encrypted_message = [None] * (self.size)
            for i in range(self.size):
                self.encrypted_message[i] = self._io.read_u1()

            self.num_metadata = self._io.read_u4le()
            if self.num_metadata > 0:
                self.entry_metadata = self._root.EntryMetadata(self._io, self, self._root)



    class FileProperties(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.level_of_confidentiality = self._io.read_u1()
            self.hash_value = [None] * (32)
            for i in range(32):
                self.hash_value[i] = self._io.read_u1()

            self.num_metadata = self._io.read_u4le()
            if self.num_metadata > 0:
                self.file_metadata = self._root.FileMetadata(self._io, self, self._root)



    class RsaPrivateKey(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            if not (self._io.is_eof()):
                self.length = self._io.read_u4le()

            if not (self._io.is_eof()):
                self.rsa_private_key = [None] * (self.length)
                for i in range(self.length):
                    self.rsa_private_key[i] = self._io.read_u1()




    class FileMetadata(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.tag = [None] * (8)
            for i in range(8):
                self.tag[i] = self._io.read_u1()

            self.length = self._io.read_u4le()
            self.value = [None] * (self.length)
            for i in range(self.length):
                self.value[i] = self._io.read_u1()



    class Header(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.magic = self._io.ensure_fixed_contents(b"\x55\x4D\x53\x45")
            self.version = (self._io.read_bytes(4)).decode(u"UTF-8")
            self.num_records_dec_table = self._io.read_u4le()
            self.num_file_entries = self._io.read_u4le()
            self.author_name_length = self._io.read_u4le()
            self.author_name = (self._io.read_bytes(self.author_name_length)).decode(u"UTF-8")


    class DecryptionTable(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.level_of_confidentiality = self._io.read_u1()
            self.aes_wrapped = [None] * (256)
            for i in range(256):
                self.aes_wrapped[i] = self._io.read_u1()



    class EntryMetadata(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.tag = [None] * (8)
            for i in range(8):
                self.tag[i] = self._io.read_u1()

            self.length = self._io.read_u4le()
            self.value = [None] * (self.length)
            for i in range(self.length):
                self.value[i] = self._io.read_u1()




