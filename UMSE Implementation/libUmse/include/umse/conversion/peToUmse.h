/////////////////// START OF PE FILE UMSE CONFIDENTIALITY CONFIGURATION ///////////////////////

// Malware sample owner
#define PE_MWR_SAMPLE_OWNER "AVFREE"

// Number of levels of confidentiality
#define PE_NUM_CONFIDENTIALITY_LEVELS 4

// PE Sections confidentiality
#define PE_DEFAULT_SECTION_CONFIDENTIALITY UNCLASSIFIED
#define PE_PE_HEADER_CONFIDENTIALITY       UNCLASSIFIED
#define PE_TEXT_SECTION_CONFIDENTIALITY    UNCLASSIFIED
#define PE_RELOC_SECTION_CONFIDENTIALITY   UNCLASSIFIED
#define PE_PDATA_SECTION_CONFIDENTIALITY   CONFIDENTIAL
#define PE_DIDAT_SECTION_CONFIDENTIALITY   CONFIDENTIAL
#define PE_RDATA_SECTION_CONFIDENTIALITY   SECRET
#define PE_DATA_SECTION_CONFIDENTIALITY    SECRET
#define PE_RSRC_SECTION_CONFIDENTIALITY    SECRET

// PE overlay confidentiality
#define PE_OVERLAY_CONFIDENTIALITY         SECRET

/////////////////// END OF PE FILE UMSE CONFIDENTIALITY CONFIGURATION ///////////////////////



// Functions
void peToUmse(int length, unsigned char* pe, unsigned int* umseLength, unsigned char** umse);
