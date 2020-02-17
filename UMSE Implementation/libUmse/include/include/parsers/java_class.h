#ifndef JAVA_CLASS_H_
#define JAVA_CLASS_H_

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

class java_class_t : public kaitai::kstruct {

public:
    class float_cp_info_t;
    class attribute_info_t;
    class method_ref_cp_info_t;
    class field_info_t;
    class double_cp_info_t;
    class long_cp_info_t;
    class invoke_dynamic_cp_info_t;
    class method_handle_cp_info_t;
    class name_and_type_cp_info_t;
    class utf8_cp_info_t;
    class string_cp_info_t;
    class method_type_cp_info_t;
    class interface_method_ref_cp_info_t;
    class class_cp_info_t;
    class constant_pool_entry_t;
    class method_info_t;
    class integer_cp_info_t;
    class field_ref_cp_info_t;

    java_class_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, java_class_t* p__root = 0);

private:
    void _read();

public:
    ~java_class_t();

    /**
     * \sa Source
     */

    class float_cp_info_t : public kaitai::kstruct {

    public:

        float_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~float_cp_info_t();

    private:
        float m_value;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        float value() const { return m_value; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class attribute_info_t : public kaitai::kstruct {

    public:
        class attr_body_code_t;
        class attr_body_exceptions_t;
        class attr_body_source_file_t;
        class attr_body_line_number_table_t;

        attribute_info_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~attribute_info_t();

        /**
         * \sa Source
         */

        class attr_body_code_t : public kaitai::kstruct {

        public:
            class exception_entry_t;

            attr_body_code_t(kaitai::kstream* p__io, java_class_t::attribute_info_t* p__parent = 0, java_class_t* p__root = 0);

        private:
            void _read();

        public:
            ~attr_body_code_t();

            /**
             * \sa Source
             */

            class exception_entry_t : public kaitai::kstruct {

            public:

                exception_entry_t(kaitai::kstream* p__io, java_class_t::attribute_info_t::attr_body_code_t* p__parent = 0, java_class_t* p__root = 0);

            private:
                void _read();

            public:
                ~exception_entry_t();

            private:
                bool f_catch_exception;
                constant_pool_entry_t* m_catch_exception;
                bool n_catch_exception;

            public:
                bool _is_null_catch_exception() { catch_exception(); return n_catch_exception; };

            private:

            public:
                constant_pool_entry_t* catch_exception();

            private:
                uint16_t m_start_pc;
                uint16_t m_end_pc;
                uint16_t m_handler_pc;
                uint16_t m_catch_type;
                java_class_t* m__root;
                java_class_t::attribute_info_t::attr_body_code_t* m__parent;

            public:

                /**
                 * Start of a code region where exception handler is being
                 * active, index in code array (inclusive)
                 */
                uint16_t start_pc() const { return m_start_pc; }

                /**
                 * End of a code region where exception handler is being
                 * active, index in code array (exclusive)
                 */
                uint16_t end_pc() const { return m_end_pc; }

                /**
                 * Start of exception handler code, index in code array
                 */
                uint16_t handler_pc() const { return m_handler_pc; }

                /**
                 * Exception class that this handler catches, index in constant
                 * pool, or 0 (catch all exceptions handler, used to implement
                 * `finally`).
                 */
                uint16_t catch_type() const { return m_catch_type; }
                java_class_t* _root() const { return m__root; }
                java_class_t::attribute_info_t::attr_body_code_t* _parent() const { return m__parent; }
            };

        private:
            uint16_t m_max_stack;
            uint16_t m_max_locals;
            uint32_t m_code_length;
            std::string m_code;
            uint16_t m_exception_table_length;
            std::vector<exception_entry_t*>* m_exception_table;
            uint16_t m_attributes_count;
            std::vector<attribute_info_t*>* m_attributes;
            java_class_t* m__root;
            java_class_t::attribute_info_t* m__parent;

        public:
            uint16_t max_stack() const { return m_max_stack; }
            uint16_t max_locals() const { return m_max_locals; }
            uint32_t code_length() const { return m_code_length; }
            std::string code() const { return m_code; }
            uint16_t exception_table_length() const { return m_exception_table_length; }
            std::vector<exception_entry_t*>* exception_table() const { return m_exception_table; }
            uint16_t attributes_count() const { return m_attributes_count; }
            std::vector<attribute_info_t*>* attributes() const { return m_attributes; }
            java_class_t* _root() const { return m__root; }
            java_class_t::attribute_info_t* _parent() const { return m__parent; }
        };

        /**
         * \sa Source
         */

        class attr_body_exceptions_t : public kaitai::kstruct {

        public:
            class exception_table_entry_t;

            attr_body_exceptions_t(kaitai::kstream* p__io, java_class_t::attribute_info_t* p__parent = 0, java_class_t* p__root = 0);

        private:
            void _read();

        public:
            ~attr_body_exceptions_t();

            class exception_table_entry_t : public kaitai::kstruct {

            public:

                exception_table_entry_t(kaitai::kstream* p__io, java_class_t::attribute_info_t::attr_body_exceptions_t* p__parent = 0, java_class_t* p__root = 0);

            private:
                void _read();

            public:
                ~exception_table_entry_t();

            private:
                bool f_as_info;
                java_class_t::class_cp_info_t* m_as_info;

            public:
                java_class_t::class_cp_info_t* as_info();

            private:
                bool f_name_as_str;
                std::string m_name_as_str;

            public:
                std::string name_as_str();

            private:
                uint16_t m_index;
                java_class_t* m__root;
                java_class_t::attribute_info_t::attr_body_exceptions_t* m__parent;

            public:
                uint16_t index() const { return m_index; }
                java_class_t* _root() const { return m__root; }
                java_class_t::attribute_info_t::attr_body_exceptions_t* _parent() const { return m__parent; }
            };

        private:
            uint16_t m_number_of_exceptions;
            std::vector<exception_table_entry_t*>* m_exceptions;
            java_class_t* m__root;
            java_class_t::attribute_info_t* m__parent;

        public:
            uint16_t number_of_exceptions() const { return m_number_of_exceptions; }
            std::vector<exception_table_entry_t*>* exceptions() const { return m_exceptions; }
            java_class_t* _root() const { return m__root; }
            java_class_t::attribute_info_t* _parent() const { return m__parent; }
        };

        /**
         * \sa Source
         */

        class attr_body_source_file_t : public kaitai::kstruct {

        public:

            attr_body_source_file_t(kaitai::kstream* p__io, java_class_t::attribute_info_t* p__parent = 0, java_class_t* p__root = 0);

        private:
            void _read();

        public:
            ~attr_body_source_file_t();

        private:
            bool f_sourcefile_as_str;
            std::string m_sourcefile_as_str;

        public:
            std::string sourcefile_as_str();

        private:
            uint16_t m_sourcefile_index;
            java_class_t* m__root;
            java_class_t::attribute_info_t* m__parent;

        public:
            uint16_t sourcefile_index() const { return m_sourcefile_index; }
            java_class_t* _root() const { return m__root; }
            java_class_t::attribute_info_t* _parent() const { return m__parent; }
        };

        /**
         * \sa Source
         */

        class attr_body_line_number_table_t : public kaitai::kstruct {

        public:
            class line_number_table_entry_t;

            attr_body_line_number_table_t(kaitai::kstream* p__io, java_class_t::attribute_info_t* p__parent = 0, java_class_t* p__root = 0);

        private:
            void _read();

        public:
            ~attr_body_line_number_table_t();

            class line_number_table_entry_t : public kaitai::kstruct {

            public:

                line_number_table_entry_t(kaitai::kstream* p__io, java_class_t::attribute_info_t::attr_body_line_number_table_t* p__parent = 0, java_class_t* p__root = 0);

            private:
                void _read();

            public:
                ~line_number_table_entry_t();

            private:
                uint16_t m_start_pc;
                uint16_t m_line_number;
                java_class_t* m__root;
                java_class_t::attribute_info_t::attr_body_line_number_table_t* m__parent;

            public:
                uint16_t start_pc() const { return m_start_pc; }
                uint16_t line_number() const { return m_line_number; }
                java_class_t* _root() const { return m__root; }
                java_class_t::attribute_info_t::attr_body_line_number_table_t* _parent() const { return m__parent; }
            };

        private:
            uint16_t m_line_number_table_length;
            std::vector<line_number_table_entry_t*>* m_line_number_table;
            java_class_t* m__root;
            java_class_t::attribute_info_t* m__parent;

        public:
            uint16_t line_number_table_length() const { return m_line_number_table_length; }
            std::vector<line_number_table_entry_t*>* line_number_table() const { return m_line_number_table; }
            java_class_t* _root() const { return m__root; }
            java_class_t::attribute_info_t* _parent() const { return m__parent; }
        };

    private:
        bool f_name_as_str;
        std::string m_name_as_str;

    public:
        std::string name_as_str();

    private:
        uint16_t m_name_index;
        uint32_t m_attribute_length;
        kaitai::kstruct* m_info;
        bool n_info;

    public:
        bool _is_null_info() { info(); return n_info; };

    private:
        java_class_t* m__root;
        kaitai::kstruct* m__parent;
        std::string m__raw_info;
        kaitai::kstream* m__io__raw_info;

    public:
        uint16_t name_index() const { return m_name_index; }
        uint32_t attribute_length() const { return m_attribute_length; }
        kaitai::kstruct* info() const { return m_info; }
        java_class_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
        std::string _raw_info() const { return m__raw_info; }
        kaitai::kstream* _io__raw_info() const { return m__io__raw_info; }
    };

    /**
     * \sa Source
     */

    class method_ref_cp_info_t : public kaitai::kstruct {

    public:

        method_ref_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~method_ref_cp_info_t();

    private:
        bool f_class_as_info;
        java_class_t::class_cp_info_t* m_class_as_info;

    public:
        java_class_t::class_cp_info_t* class_as_info();

    private:
        bool f_name_and_type_as_info;
        java_class_t::name_and_type_cp_info_t* m_name_and_type_as_info;

    public:
        java_class_t::name_and_type_cp_info_t* name_and_type_as_info();

    private:
        uint16_t m_class_index;
        uint16_t m_name_and_type_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t class_index() const { return m_class_index; }
        uint16_t name_and_type_index() const { return m_name_and_type_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class field_info_t : public kaitai::kstruct {

    public:

        field_info_t(kaitai::kstream* p__io, java_class_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~field_info_t();

    private:
        bool f_name_as_str;
        std::string m_name_as_str;

    public:
        std::string name_as_str();

    private:
        uint16_t m_access_flags;
        uint16_t m_name_index;
        uint16_t m_descriptor_index;
        uint16_t m_attributes_count;
        std::vector<attribute_info_t*>* m_attributes;
        java_class_t* m__root;
        java_class_t* m__parent;

    public:
        uint16_t access_flags() const { return m_access_flags; }
        uint16_t name_index() const { return m_name_index; }
        uint16_t descriptor_index() const { return m_descriptor_index; }
        uint16_t attributes_count() const { return m_attributes_count; }
        std::vector<attribute_info_t*>* attributes() const { return m_attributes; }
        java_class_t* _root() const { return m__root; }
        java_class_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class double_cp_info_t : public kaitai::kstruct {

    public:

        double_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~double_cp_info_t();

    private:
        double m_value;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        double value() const { return m_value; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class long_cp_info_t : public kaitai::kstruct {

    public:

        long_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~long_cp_info_t();

    private:
        uint64_t m_value;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint64_t value() const { return m_value; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class invoke_dynamic_cp_info_t : public kaitai::kstruct {

    public:

        invoke_dynamic_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~invoke_dynamic_cp_info_t();

    private:
        uint16_t m_bootstrap_method_attr_index;
        uint16_t m_name_and_type_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t bootstrap_method_attr_index() const { return m_bootstrap_method_attr_index; }
        uint16_t name_and_type_index() const { return m_name_and_type_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class method_handle_cp_info_t : public kaitai::kstruct {

    public:

        enum reference_kind_enum_t {
            REFERENCE_KIND_ENUM_GET_FIELD = 1,
            REFERENCE_KIND_ENUM_GET_STATIC = 2,
            REFERENCE_KIND_ENUM_PUT_FIELD = 3,
            REFERENCE_KIND_ENUM_PUT_STATIC = 4,
            REFERENCE_KIND_ENUM_INVOKE_VIRTUAL = 5,
            REFERENCE_KIND_ENUM_INVOKE_STATIC = 6,
            REFERENCE_KIND_ENUM_INVOKE_SPECIAL = 7,
            REFERENCE_KIND_ENUM_NEW_INVOKE_SPECIAL = 8,
            REFERENCE_KIND_ENUM_INVOKE_INTERFACE = 9
        };

        method_handle_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~method_handle_cp_info_t();

    private:
        reference_kind_enum_t m_reference_kind;
        uint16_t m_reference_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        reference_kind_enum_t reference_kind() const { return m_reference_kind; }
        uint16_t reference_index() const { return m_reference_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class name_and_type_cp_info_t : public kaitai::kstruct {

    public:

        name_and_type_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~name_and_type_cp_info_t();

    private:
        bool f_name_as_info;
        java_class_t::utf8_cp_info_t* m_name_as_info;

    public:
        java_class_t::utf8_cp_info_t* name_as_info();

    private:
        bool f_name_as_str;
        std::string m_name_as_str;

    public:
        std::string name_as_str();

    private:
        bool f_descriptor_as_info;
        java_class_t::utf8_cp_info_t* m_descriptor_as_info;

    public:
        java_class_t::utf8_cp_info_t* descriptor_as_info();

    private:
        bool f_descriptor_as_str;
        std::string m_descriptor_as_str;

    public:
        std::string descriptor_as_str();

    private:
        uint16_t m_name_index;
        uint16_t m_descriptor_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t name_index() const { return m_name_index; }
        uint16_t descriptor_index() const { return m_descriptor_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class utf8_cp_info_t : public kaitai::kstruct {

    public:

        utf8_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~utf8_cp_info_t();

    private:
        uint16_t m_str_len;
        std::string m_value;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t str_len() const { return m_str_len; }
        std::string value() const { return m_value; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class string_cp_info_t : public kaitai::kstruct {

    public:

        string_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~string_cp_info_t();

    private:
        uint16_t m_string_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t string_index() const { return m_string_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class method_type_cp_info_t : public kaitai::kstruct {

    public:

        method_type_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~method_type_cp_info_t();

    private:
        uint16_t m_descriptor_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t descriptor_index() const { return m_descriptor_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class interface_method_ref_cp_info_t : public kaitai::kstruct {

    public:

        interface_method_ref_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~interface_method_ref_cp_info_t();

    private:
        bool f_class_as_info;
        java_class_t::class_cp_info_t* m_class_as_info;

    public:
        java_class_t::class_cp_info_t* class_as_info();

    private:
        bool f_name_and_type_as_info;
        java_class_t::name_and_type_cp_info_t* m_name_and_type_as_info;

    public:
        java_class_t::name_and_type_cp_info_t* name_and_type_as_info();

    private:
        uint16_t m_class_index;
        uint16_t m_name_and_type_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t class_index() const { return m_class_index; }
        uint16_t name_and_type_index() const { return m_name_and_type_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class class_cp_info_t : public kaitai::kstruct {

    public:

        class_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~class_cp_info_t();

    private:
        bool f_name_as_info;
        java_class_t::utf8_cp_info_t* m_name_as_info;

    public:
        java_class_t::utf8_cp_info_t* name_as_info();

    private:
        bool f_name_as_str;
        std::string m_name_as_str;

    public:
        std::string name_as_str();

    private:
        uint16_t m_name_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t name_index() const { return m_name_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class constant_pool_entry_t : public kaitai::kstruct {

    public:

        enum tag_enum_t {
            TAG_ENUM_UTF8 = 1,
            TAG_ENUM_INTEGER = 3,
            TAG_ENUM_FLOAT = 4,
            TAG_ENUM_LONG = 5,
            TAG_ENUM_DOUBLE = 6,
            TAG_ENUM_CLASS_TYPE = 7,
            TAG_ENUM_STRING = 8,
            TAG_ENUM_FIELD_REF = 9,
            TAG_ENUM_METHOD_REF = 10,
            TAG_ENUM_INTERFACE_METHOD_REF = 11,
            TAG_ENUM_NAME_AND_TYPE = 12,
            TAG_ENUM_METHOD_HANDLE = 15,
            TAG_ENUM_METHOD_TYPE = 16,
            TAG_ENUM_INVOKE_DYNAMIC = 18
        };

        constant_pool_entry_t(kaitai::kstream* p__io, java_class_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~constant_pool_entry_t();

    private:
        tag_enum_t m_tag;
        kaitai::kstruct* m_cp_info;
        bool n_cp_info;

    public:
        bool _is_null_cp_info() { cp_info(); return n_cp_info; };

    private:
        java_class_t* m__root;
        java_class_t* m__parent;

    public:
        tag_enum_t tag() const { return m_tag; }
        kaitai::kstruct* cp_info() const { return m_cp_info; }
        java_class_t* _root() const { return m__root; }
        java_class_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class method_info_t : public kaitai::kstruct {

    public:

        method_info_t(kaitai::kstream* p__io, java_class_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~method_info_t();

    private:
        bool f_name_as_str;
        std::string m_name_as_str;

    public:
        std::string name_as_str();

    private:
        uint16_t m_access_flags;
        uint16_t m_name_index;
        uint16_t m_descriptor_index;
        uint16_t m_attributes_count;
        std::vector<attribute_info_t*>* m_attributes;
        java_class_t* m__root;
        java_class_t* m__parent;

    public:
        uint16_t access_flags() const { return m_access_flags; }
        uint16_t name_index() const { return m_name_index; }
        uint16_t descriptor_index() const { return m_descriptor_index; }
        uint16_t attributes_count() const { return m_attributes_count; }
        std::vector<attribute_info_t*>* attributes() const { return m_attributes; }
        java_class_t* _root() const { return m__root; }
        java_class_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class integer_cp_info_t : public kaitai::kstruct {

    public:

        integer_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~integer_cp_info_t();

    private:
        uint32_t m_value;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint32_t value() const { return m_value; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

    /**
     * \sa Source
     */

    class field_ref_cp_info_t : public kaitai::kstruct {

    public:

        field_ref_cp_info_t(kaitai::kstream* p__io, java_class_t::constant_pool_entry_t* p__parent = 0, java_class_t* p__root = 0);

    private:
        void _read();

    public:
        ~field_ref_cp_info_t();

    private:
        bool f_class_as_info;
        java_class_t::class_cp_info_t* m_class_as_info;

    public:
        java_class_t::class_cp_info_t* class_as_info();

    private:
        bool f_name_and_type_as_info;
        java_class_t::name_and_type_cp_info_t* m_name_and_type_as_info;

    public:
        java_class_t::name_and_type_cp_info_t* name_and_type_as_info();

    private:
        uint16_t m_class_index;
        uint16_t m_name_and_type_index;
        java_class_t* m__root;
        java_class_t::constant_pool_entry_t* m__parent;

    public:
        uint16_t class_index() const { return m_class_index; }
        uint16_t name_and_type_index() const { return m_name_and_type_index; }
        java_class_t* _root() const { return m__root; }
        java_class_t::constant_pool_entry_t* _parent() const { return m__parent; }
    };

private:
    std::string m_magic;
    uint16_t m_version_minor;
    uint16_t m_version_major;
    uint16_t m_constant_pool_count;
    std::vector<constant_pool_entry_t*>* m_constant_pool;
    uint16_t m_access_flags;
    uint16_t m_this_class;
    uint16_t m_super_class;
    uint16_t m_interfaces_count;
    std::vector<uint16_t>* m_interfaces;
    uint16_t m_fields_count;
    std::vector<field_info_t*>* m_fields;
    uint16_t m_methods_count;
    std::vector<method_info_t*>* m_methods;
    uint16_t m_attributes_count;
    std::vector<attribute_info_t*>* m_attributes;
    java_class_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::string magic() const { return m_magic; }
    uint16_t version_minor() const { return m_version_minor; }
    uint16_t version_major() const { return m_version_major; }
    uint16_t constant_pool_count() const { return m_constant_pool_count; }
    std::vector<constant_pool_entry_t*>* constant_pool() const { return m_constant_pool; }
    uint16_t access_flags() const { return m_access_flags; }
    uint16_t this_class() const { return m_this_class; }
    uint16_t super_class() const { return m_super_class; }
    uint16_t interfaces_count() const { return m_interfaces_count; }
    std::vector<uint16_t>* interfaces() const { return m_interfaces; }
    uint16_t fields_count() const { return m_fields_count; }
    std::vector<field_info_t*>* fields() const { return m_fields; }
    uint16_t methods_count() const { return m_methods_count; }
    std::vector<method_info_t*>* methods() const { return m_methods; }
    uint16_t attributes_count() const { return m_attributes_count; }
    std::vector<attribute_info_t*>* attributes() const { return m_attributes; }
    java_class_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // JAVA_CLASS_H_
