#include <stdio.h>
#include <time.h>
#include "tools.h"
#include "files.h"
#include "user_input.h"

/**
 * @brief Get the id of the next text from id_cnt.txt file
 */
uint32_t get_id()
{
    uint32_t next_id = 0;
    FILE *fd;
    char file_name[NAME_LEN];
    strncpy(file_name, FILE_PATH, sizeof(file_name));
    strcat(file_name, "id_cnt.txt");
    fd = fopen(file_name, "r");
    if (fd == NULL)
    {
        fd = fopen(file_name, "w");
        fprintf(fd,"%"PRIu32"", next_id);
        fclose(fd);
    }
    else
    {
        fscanf(fd, "%"SCNu32"", &next_id);
        fclose(fd);
    }
    return next_id;
}

/**
 * @brief saves the new id counter to id_cnt.txt file, replacing the old value.
 */
void save_id(uint32_t id)
{
    FILE *fd;
    char file_name[NAME_LEN];
    strncpy(file_name, FILE_PATH, sizeof(file_name));
    strcat(file_name, "id_cnt.txt");
    fd = fopen(file_name, "w");
    if (fd)
    {
        fprintf(fd, "%"PRIu32"", id);
        fclose(fd);
    }
}

/**
 * @brief save the test info to the file. creates a file with a name as the 
 * test id, and saves the time the test was initiated, the test id, the 
 * result of the test (1 is success, 255 is failure) and the time it took 
 * for the test to be completed and sent back to the client.
 */
void save_test_to_file(uint32_t test_id, uint8_t test_result, double time_delta)
{
    FILE *fd;
    char file_name[NAME_LEN];
    strncpy(file_name, FILE_PATH, sizeof(file_name));
    char id_str[ID_LEN]; 
    sprintf(id_str, "%"PRIu32"", test_id);
    strcat(file_name, id_str);
    fd = fopen(file_name, "w");

    time_t rawtime;
    struct tm * timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    if (fd)
    {
        fprintf(fd, "%d.%d.%d, %02d:%02d:%02d\n", 
                timeinfo->tm_mday, timeinfo->tm_mon + MONTH_FIX, 
                timeinfo->tm_year + YEAR_FIX, timeinfo->tm_hour,
                timeinfo->tm_min, timeinfo->tm_sec);
        fprintf(fd, "Test ID: %"PRIu32"\n", test_id);
        fprintf(fd, "%"PRIu8"\n", test_result);
        fprintf(fd, "Test took: %g seconds\n", time_delta);
    }
    else
    {
        printf("Failed to open file.\n");
    }
    fclose(fd);
}