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

typedef enum Digit{
         /*gfedcba*/ 
    d0 = 0b0111111,
    d1 = 0b0001010,
    d2 = 0b1010111,
    d3 = 0b1001111,
    d4 = 0b1101010,
    d5 = 0b1101101,
    d6 = 0b1111101,
    d7 = 0b0001011,
    d8 = 0b1111111,
    d9 = 0b1101111
} digit;

typedef bool display[5][3];
typedef uint digits[LEN];

uint map[] = {d0, d1, d2, d3, d4, d5, d6, d7, d8, d9};

void turn_on_segment(display disp, uint b){
/*
display :
  0 1 2
0 # # #
1 #   #
2 # # #
3 #   #
4 # # #
*/
    switch(b)
    {
        case 0b0000001:
            disp[0][0] = true;
            disp[0][1] = true;
            disp[0][2] = true;
            break;
        case 0b0000010:
            disp[0][2] = true;
            disp[1][2] = true;
            disp[2][2] = true;
            break;
        case 0b0000100:
            disp[4][0] = true;
            disp[4][1] = true;
            disp[4][2] = true;
            break;
        case 0b0001000:
            disp[2][2] = true;
            disp[3][2] = true;
            disp[4][2] = true;
            break;
        case 0b0010000:
            disp[2][0] = true;
            disp[3][0] = true;
            disp[4][0] = true;
            break;
        case 0b0100000:
            disp[0][0] = true;
            disp[1][0] = true;
            disp[2][0] = true;
            break;
        case 0b1000000:
            disp[2][0] = true;
            disp[2][1] = true;
            disp[2][2] = true;
            break;
    }
}

uint count_segments(digit d){
    uint seg = 0;
    for (uint i = 0; i < SEGMENTS; i++)
        if(d & (1 << i))
            seg++;
    return seg;
}

uint count_all_segments(digits dig){
    uint i = 0, seg = 0;
    while(dig[i]){
        seg += count_segments(dig[i]);
        i++;
    }
    return seg;
}

void turn_on_digit(display disp, digit d){
    for (uint i = 0; i < SEGMENTS; i++){
        if(d & (1 << i)){
            turn_on_segment(disp, 1 << i);
        }
    }
}

void show_display(display disp){
    for(uint i = 0; i < ROWS; i++){
        for(uint j = 0; j < COLS; j++){
            if(disp[i][j])
                printf("# ");
            else
                printf("  ");
        }
        printf("\n");
    }
}

void clear_display(display disp){
    for(uint i = 0; i < ROWS; i++)
        for(uint j = 0; j < COLS; j++)
            disp[i][j] = false;
}

void uint_to_digits(uint n,  digits dig){
    uint i = 0;
    while(n){
        if(i >= LEN){
            printf("number of digits should be less then %d\n", LEN + 1);
            exit(1);
        }
        dig[i] = map[n%10];
        n/=10;
        i++;
    }
}

uint distance(digit d1, digit d2){
    uint dist = 0;
    for (uint i = 0; i < SEGMENTS; i++){
        if((d1 & (1 << i)) != (d2 & (1 << i)))
            dist++;
    } 
    return dist;
}

uint full_distance(digits dig1, digits dig2){
    uint i = 0, dist = 0;
    while(dig1[i] || dig1[i]){
        dist += distance(dig1[i], dig2[i]);
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
    uint l = num_len(n), 
        min = get_min(l),
        max = get_max(l),
        M = 0,
        dist = moves * 2,
        segments = count_all_segments(dig1);
    for(uint i = min; i < max + 1; i++){
        digits dig2 = {0};
        uint_to_digits(i, dig2);
        if(full_distance(dig1, dig2) == dist &&
            count_all_segments(dig2) == segments){
            M = i;
        }
    }
    return M;
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