/***   iOS Extension formats
 *
 * Support for iOS extension formats
 * StorageMetadata - Uuid of storage metadata
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>

#define COMPILE_SQLITE_EXTENSIONS_AS_LOADABLE_MODULE 1
#include "sqlite3ext.h"
SQLITE_EXTENSION_INIT1

#define INDENT_INCREMENT 4

#define ERROR_NONE 0
#define ERROR_INSUFFICIENT_MEMORY 1
#define ERROR_INVALID_HEADER 2
#define ERROR_INVALID_TRAILER 3
#define ERROR_INVALID_OFFSET 4
#define ERROR_INVALID_OBJECT_LENGTH 5
#define ERROR_INVALID_REFERENCE 6
#define ERROR_INVALID_CHARACTER 7

const unsigned char MAGIC[4] = { 0x03, 0x23, 0x23, 0x23 };
const int BUFFER_SIZE = 1024;

typedef struct externalStorage_hdr {
    unsigned char magic[sizeof(MAGIC)];
    unsigned int sz;
    unsigned int crap;
    unsigned char uuid[16];
    unsigned char path[0x24];
} ExternalStorage_Hdr;


int get_byte(char c)
{
    return c & 0xff;
}

char *get_uuid(char *uuid, size_t sz)
{
    char *buffer = malloc(BUFFER_SIZE);
    sprintf(buffer, " ");
    for (int i=0; i<sz-1; i++) {
        sprintf(buffer, "%s%#x, ", buffer, get_byte(uuid[i]));
    }
    sprintf(buffer, "%s%#x\n", buffer, get_byte(uuid[sz-1]));

    /* long line */
    sprintf(buffer, "%s\t\t", buffer);
    for (int i=0; i<sz; i++) {
        sprintf(buffer, "%s%x", buffer, get_byte(uuid[i]));
    }

    return buffer;
}

int decodeExternalStorageBlob(unsigned char **result, const char *data, int dataLength)
{
    const char fname[] = "decodeExternalStorageBlob";
    char *output = malloc(1024);
    ExternalStorage_Hdr *ex_storage = (ExternalStorage_Hdr *) data;
    if (memcmp(MAGIC, ex_storage->magic, sizeof(MAGIC)))
    {
        printf("[%s] Bad Magic for External Storage Blob\n", fname);
        return ERROR_INVALID_HEADER;
    }

    sprintf(output, "Size: %#x (%d)\n", ex_storage->sz, ex_storage->sz);
    sprintf(output, "%sUuid: %s\n", output, get_uuid(ex_storage->uuid, 16));
    sprintf(output, "%sFilename: %s\n", output, ex_storage->path);
    *result = output;

    return ERROR_NONE;
}

/**  Wrapper functions
 *
 */

void freeResult(void *ptr)
{
    if (ptr != NULL)
        free(ptr);
    return;
}

static void externalStorageFunc(sqlite3_context *context, int argc, sqlite3_value **argv)
{
    const char fname[] = "externalStorageFunc";
    int resultLength;
    int errorCode = 0;
    unsigned char *result = NULL;
    assert(argc == 1);
    switch (sqlite3_value_type(argv[0]))
    {
        case SQLITE_TEXT: 
        case SQLITE_BLOB:
            {
                const char *data = sqlite3_value_text(argv[0]);
                int dataLength = sqlite3_value_bytes(argv[0]);
                errorCode = decodeExternalStorageBlob(&result, data, dataLength);
                if (errorCode == ERROR_NONE)
                {
                    resultLength = strlen(result);
                    sqlite3_result_text(context, result, resultLength, &freeResult);
                }
                else
                {
                    printf("[%s] Error decoding blob \n", fname);
                    if (sqlite3_value_type(argv[0]) == SQLITE_TEXT) {
                        sqlite3_result_text(context, data, dataLength, NULL);
                    } else
                        sqlite3_result_blob(context, data, dataLength, NULL);
                }
                break;
            }
        default:
            {
                sqlite3_result_null(context);
                break;
            }
    }
}

/** Register iOS Extension formats
 *
 * Register the parsing functions with sqlite
 */

void RegisterExtensionFormats(sqlite3 *db)
{
    sqlite3_create_function(db, "storaged", 1, 0, db, externalStorageFunc, 0, 0);
}

#ifdef COMPILE_SQLITE_EXTENSIONS_AS_LOADABLE_MODULE

#ifdef _WIN32
__declspec(dllexport)
#endif

// int sqlite3_ios_init(sqlite3 *db, char **pzErrMsg, const sqlite3_api_routines *pApi)
int sqlite3_extension_init(sqlite3 *db, char **pzErrMsg, const sqlite3_api_routines *pApi)
{
    int rc = SQLITE_OK;
    SQLITE_EXTENSION_INIT2(pApi);
    RegisterExtensionFormats(db);
    return rc;
}

#endif /**/ COMPILE_SQLITE_EXTENSIONS_AS_LOADABLE_MODULE */

