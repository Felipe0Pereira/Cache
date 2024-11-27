#include "iobench.h"

int main() {
    // opens a file called `data` with write "w" mode
    FILE *file = fopen("data", "w");
    
    if (!file) {
        perror("fopen");
        exit(1);
    }

    // writes the characer '6' to the file
    size_t size = 5120000;
    const char* buf = "6";
    double start = tstamp();

    size_t n = 0;
    while (n < size) {
        ssize_t r = fwrite(buf, 1, 1, file);
        if (r != 1) {
            perror("fwrite");
            exit(1);
        }

        // with some frequency (defined in iobench.h), prints out
        // how long it takes to complete the write.
        n += r;
        if (n % PRINT_FREQUENCY == 0) {
            report(n, tstamp() - start);
        }
    }

    fclose(file);
    report(n, tstamp() - start);
    fprintf(stderr, "\n");
}
