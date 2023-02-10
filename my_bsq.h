#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>

struct  vars_info {
    int i, j, size;
};
int my_size(char* str);
char* read_line(int fd);
int determine_height(char* str);
int define_the_width(char* s);
char** finf_null(char* map);
char* read_file(char*file);
unsigned short** fill_to_binary(char* my_map, int width, int height);
int find_minimal_num(unsigned short **buf, int x, int y);
struct  vars_info* send_result_for_check_map(unsigned short **temp,unsigned short** matrix,struct  vars_info* ans, int h, int w);
struct vars_info* check_map(unsigned short** matrix, int wid, int hei);