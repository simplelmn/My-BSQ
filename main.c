#include "my_bsq.h"

int main(int ac, char** av)
{
    if (ac < 2) {
        puts("less argument");
        exit(1);
    } else if (!open(av[1], O_RDONLY)){
        puts("Map not found");
        exit(1);
    }
    char* map = read_file(av[1]);

    int h = determine_height(map);
    int w = define_the_width(map);

    unsigned short** full_map =  fill_to_binary(map, w, h);

    struct  vars_info* info = check_map(full_map, w, h);
    
    char** char_map = finf_null(av[1]);
    
    for(int i=0; i <= info->size; i++) {
        for(int j=0; j <= info->size; j++) {
            char_map[info->j-i][info->i-j] = 'x';
        }
    }
    for(int i = 0; char_map[i]; i++){
        printf("%s\n", char_map[i]);
    }
}