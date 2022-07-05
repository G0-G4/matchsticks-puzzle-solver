/*
  a
f   b
  g
e   d
  c
0b00000000
   gfedcba         
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

#define ROWS 5
#define COLS 3
#define SEGMENTS 7
#define LEN 10

typedef unsigned int uint;

typedef bool display[5][3];
typedef uint digits[LEN];

/*
there is an additional row and column
for finding distance between a digit and an empty spcace.
I thought it would help to adapt program for working with numbers
with different lengths, but it didn't

*/
uint distance[11][11] = {
    {0, 4, 3, 3, 4, 3, 2, 3, 1, 2, 6},
    {4, 0, 5, 3, 2, 5, 6, 1, 5, 4, 2},
    {3, 5, 0, 2, 5, 4, 3, 4, 2, 3, 5},
    {3, 3, 2, 0, 3, 2, 3, 2, 2, 1, 5},
    {4, 2, 5, 3, 0, 3, 4, 3, 3, 2, 4},
    {3, 5, 4, 2, 3, 0, 1, 4, 2, 1, 5},
    {2, 6, 3, 3, 4, 1, 0, 5, 1, 2, 6},
    {3, 1, 4, 2, 3, 4, 5, 0, 4, 3, 3},
    {1, 5, 2, 2, 3, 2, 1, 4, 0, 1, 7},
    {2, 4, 3, 1, 2, 1, 2, 3, 1, 0, 6},
    {6, 2, 5, 5, 4, 5, 6, 3, 7, 6, 0},
};

uint segments[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

uint count_all_segments(digits dig){
    uint i = 0, seg = 0;
    while(dig[i] != 10){
        seg += segments[dig[i]];
        i++;
    }
    return seg;
}

void print_digits(digits d){
    for(int i = 0; i < LEN; i++)
        printf("%d ", d[i]);
    printf("\n");
}

void uint_to_digits(uint n,  digits dig){
    uint i = 0;
    if (n != 0){
        while(n){
            if(i >= LEN){
                printf("number of digits should be less then %d\n", LEN + 1);
                exit(1);
            }
            dig[i] = n%10;
            n/=10;
            i++;
        }
        dig[i] = 10;
    }
    else
        dig[i] = 10;
}

uint full_distance(digits dig1, digits dig2){
    uint i = 0, dist = 0;
    while(dig1[i] != 10 || dig2[i] != 10){
        dist += distance[dig1[i]][dig2[i]];
        i++;
    }
    return dist;
}

uint num_len(uint n){
    uint l = 0;
    while(n/=10)
        l++;
    return l;
}

uint get_min(uint len){
    uint n = 1;
    for(uint i = 0; i < len; i++)
        n *= 10;
    return n;
}

uint get_max(uint len){
    uint n = 9;
    for(uint i = 0; i < len; i++){
        n *= 10;
        n += 9;
    }
    return n;
}

uint find_max(uint n, uint moves){
    digits dig1 = {0};
    uint_to_digits(n, dig1);
    print_digits(dig1);
    uint l = num_len(n), 
        min = get_min(l),
        max = get_max(l),
        dist = moves * 2,
        segments = count_all_segments(dig1);
    for(uint i = max; i >= min; i--){
        digits dig2 = {0};
        uint_to_digits(i, dig2);
        if(full_distance(dig1, dig2) == dist &&
            count_all_segments(dig2) == segments){
            return i;
        }
    }
    return -1;
}

uint str_to_uint(const char* str){
    uint n;
    char* end;
    n = strtoul(str, &end, 10);
    if (*end != '\0' || errno == ERANGE || (int)n < 0)
        exit(1);
    return n;
}

int main(int argc, char** argv){
    if(argc < 3){
        printf("need number and number of moves");
    }
    uint n, mov;
    n   = str_to_uint(argv[1]);
    mov = str_to_uint(argv[2]);
    printf("%d\n", find_max(n, mov));
    return 0;
}