#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

/**
 * Read the data from a compressed file and return the number of files in this file.
 * 
 * buf: if the mode is 0, the buf is the file name, read it from disk.
 *      if the mode is 1, the buf is the real data stored in the memory.
 * mode: just shown in the buf, if the mode is neither 0 nor 1, the function will just return 0.
 * size: what long bytes shold be read for archive struct.
 * sum: just record the sum of the number stored in the file with name XX.
 * 
 * What's more about libarchive, please checkout in https://github.com/libarchive/libarchive.
 **/
size_t read_data(const void const *buf, int mode, size_t size, unsigned long *sum)
{
    int r, len;
    mode_t type;
    size_t count = 0;
    struct archive *a;
    struct archive_entry *entry;
    const char* subname;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    if (mode == 0)
        r = archive_read_open_filename(a, (const char *)buf, size);
    else if (mode == 1)
        r = archive_read_open_memory(a, (void *)buf, size);
    else
        goto finish;

    if (r != ARCHIVE_OK)
        goto finish;

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        type = archive_entry_filetype(entry);
        subname = archive_entry_pathname(entry);

        // skip the folder produced by the libarchive.
        if (type == AE_IFREG)
        {
            size_t bufsize = archive_entry_size(entry);
            char* buf = malloc(bufsize + 1);
            buf[bufsize] = '\0';
            archive_read_data(a, buf, bufsize);

            if (strlen(subname) == 2)   // this is a file with the number, read it.
            {
                int number = atoi(buf);
                *sum = *sum + number;
                count++;
            }
            else if (strlen(subname) > 3) // this is a compressed file with tar.gz, so recursive read it.
            {
                count += read_data(buf, 1, bufsize, sum);
            }
            free(buf);
        }
        archive_read_data_skip(a);
    }

finish:
    r = archive_read_free(a);
    return count;
}

int main(int argc, char const *argv[])
{
    unsigned long sum = 0;
    size_t count = read_data("00.tar.gz", 0, 10240, &sum);
    printf("The number of files is %lu, and the sum is %lu\n", count, sum);
    return 0;
}

