#include "my_bsq.h"

int my_size(char* str){
    int i = 0;
    while(str[i]){
        i++;
    }
    return i;
}

char* read_line(int fd)
{
    char *temp = (char*)malloc(sizeof(char)*100);
    int i = 0, r;
    char c;
    while ((r = read(fd, &c, 1)) >= 0)
    {
        if (r == 0 && i == r) return NULL;
        if (c == '\n' || r == 0) break;
        temp[i] = c;
        i++;
    }
    temp[i] = '\0';
    char* ret = (char*)malloc(sizeof(char) * i);
    strcpy(ret, temp);
    return ret;
}

int determine_height(char* str) {
        int length = 0, i=0;
        while(str[i] != '\0'){
            if(str[i] == '\n') length++;
            i++;
        }
        return length+1;
}
int define_the_width(char* s) {
        int i=0;
        for(;s[i] != '\n';)
            i++;
        return i;
}

char** finf_null(char* map)
{
    const int fd = open(map, O_RDONLY);
    int num_read_lines = atoi(read_line(fd));
    char* row = read_line(fd);
    char** matrix = (char**)malloc(num_read_lines * my_size(row));
    matrix[0] = row;
    int i = 1;
    for(;(row = read_line(fd)) != NULL;){
        matrix[i] = row;
        i++;
    }
        
    matrix[i] = NULL;
    return matrix;
}

char* read_file(char*file) {
    int fd = open(file, O_RDONLY);
    struct stat fs;
    stat(file, &fs);
    char *readlines = read_line(fd);
    char* map = malloc(sizeof(char)*(fs.st_size+1 - my_size(readlines)));
    off_t read_able = fs.st_size - my_size(readlines);
    if(read(fd, map, read_able)) {
        map[read_able] = '\0';
    }
    return map;
}

unsigned short** fill_to_binary(char* my_map, int width, int height) {
    unsigned short **map = malloc(sizeof(unsigned short *) * height);
    for(int l=0; l < height; l++) // init short array
        map[l] = malloc(sizeof(unsigned short*) * width);

     int l = 0,j=0;
     for(int i=0; my_map[i]!='\0'; i++)
        if (my_map[i] == '\n') l++, j=0;
        else
            map[l][j++] = (my_map[i] == '.'); // fill array
    return map;
}

int find_minimal_num(unsigned short **buf, int x, int y) { // set minimum
    unsigned short min = buf[y][x-1];
    if (min > buf[y-1][x-1])
        min = buf[y-1][x-1];
    if (min > buf[y-1][x])
        min = buf[y-1][x];
    if(min != 0) {
        buf[y][x] = min+1;
        return (int)min;
    }
    else
        buf[y][x] = 1;
    return 0;
}

struct  vars_info* send_result_for_check_map(unsigned short **temp,unsigned short** matrix,struct  vars_info* ans, int h, int w){
    int len;
    for(int i=0; i < h; i++) {
        for(int j=0; j<w; j++) {
            if(matrix[i][j] != 0) {
                len = find_minimal_num(temp, j+1, i+1);
                if(len > ans->size) {
                    ans->i = j;
                    ans->j = i;
                    ans->size = len;
                }
            }
            else
                temp[i+1][j+1] = matrix[i][j];
        }
    }
    return ans;
}

struct vars_info* check_map(unsigned short** matrix, int wid, int hei) {
    struct  vars_info* result = malloc(sizeof(struct  vars_info));
    result->i = 0;
    result->j = 0;
    result->size = 0;
    unsigned short **temp = malloc(sizeof(unsigned short*) * (hei+1));
    for(int i = 0; i < hei + 1; i++){
        temp[i] = malloc(sizeof(unsigned short*) * (wid+1));
    }
    int y = 0;
    while( y<wid)
        temp[0][y++] = 0;
    y = 0;
    while(y<hei)
        temp[y++][0] = 0;
    return send_result_for_check_map(temp, matrix, result, hei , wid);
}
