/* program that prints the type of CPU it is running on and the
 * number of cores it has.the program is written in C and uses
    * the POSIX sysconf() function to get the number of cores.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>


// declare and define the function to get type of CPU
// declare and define the function to get number of cores
int get_cpu_type(void)
{
    FILE *cpuinfo;
    char line[128];
    char *cputype;
    cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    while (fgets(line, 128, cpuinfo) != NULL)
    {
        if (strncmp(line, "model name", 10) == 0)
        {
            cputype = strchr(line, ':') + 2;
            printf("CPU type: %s\n", cputype);
            fclose(cpuinfo);
            return 0;
        }
    }
    fclose(cpuinfo);
    return 0;
}

int get_cpu_cores(void)
{
    int cores;
    cores = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of cores: %d\n", cores);
    return 0;
}

// main function
int main(void)
{
    get_cpu_type();
    get_cpu_cores();
    return 0;
}
