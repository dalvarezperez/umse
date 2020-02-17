/////////////////// START OF RAW FILE UMSE CONFIDENTIALITY CONFIGURATION ///////////////////////

// Malware sample owner
#define RAW_MWR_SAMPLE_OWNER "AVFREE"

// Number of levels of confidentiality
#define RAW_NUM_CONFIDENTIALITY_LEVELS 4

// RAW confidentiality
#define RAW_VERY_LOW_CONFIDENTIALITY   UNCLASSIFIED
#define RAW_LOW_CONFIDENTIALITY        CONFIDENTIAL
#define RAW_MEDIUM_CONFIDENTIALITY     RESTRICTED
#define RAW_DEFAULT_CONFIDENTIALITY    SECRET

/////////////////// END OF RAW FILE UMSE CONFIDENTIALITY CONFIGURATION ///////////////////////


// Functions
void rawToUmse(int length, unsigned char* raw, unsigned int* rawLength, unsigned char** umse);
