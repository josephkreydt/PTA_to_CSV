//
//  main.c
//  PTA to CSV
//
//  Created by Kreydt on 10/30/21.
//

#include <stdio.h>
#include <regex.h>

/* you're out of a chunk when you hit a space (ascii 32)
   unless the space is within a comment or description or stock amount.
   so, unless you are in comment_mode, descr_mode, or stock_mode,
   then you just need to replace spaces with commas
*/

// Function to check for number
int check_for_number(int input)
{
    // Convert input int to char so it can be passed into regexec function
    const char c = input;
    // Variable to store initial regex()
    regex_t regex;
     
    // Variable for return type
    int value;
     
    // Creation of regEx
    // 48-57 are ASCII values representing 0-9
    value = regcomp(&regex, "[48-57]", 0);
     
    // Comparing pattern "GeeksforGeeks" with
    // string in reg
    value = regexec(&regex, &c, 0, NULL, 0);
    
    // If pattern found
    if (value == 0) {
        printf("Pattern found.\n");
    }
    // If pattern not found
    else if (value == REG_NOMATCH) {
        printf("Pattern not found.\n");
    }
    // If error occured during Pattern
    // matching
    else {
        printf("An error occured during regex pattern matching.\n");
    }
    
    return value;
}

int determine_chunk_type(int c, int previous_c, int previous_c_2) {
    int chunk_type;
    int number = check_for_number(c);
    if (number) {
        /* if it's a number, it's either a date, amount/stock, or descr */
        if (previous_c == 32 && previous_c_2 != 32) /* if previous char is a space, but one before that is not */ {
            /* then it's a descr */
            chunk_type = 2;
        } else if (previous_c_2 == 32 && previous_c == 32) /* if previous 2 chars are spaces */ {
            /* then it's an amount/stock */
            chunk_type = 5;
        } else /* if both previous chars are not spaces */ {
            /* then it's a date */
            chunk_type = 1;
        }
    } else {
        /* if it's not a number, it's no chunk, descr, to account, from account, or comment */
        chunk_type = 0;
    }
    
    return chunk_type;
}

int main(int argc, const char * argv[]) {
    int c;
    int previous_c = 0;
    int previous_c_2 = 0;
    int chunk_type = 0;
    /* 0 is no chunk
       1 is date chunk
       2 is descr chunk
       3 is to account chunk
       4 is from account chunk
       5 is amount chunk
       6 is comment chunk */
    FILE *file;
    file = fopen("/Users/joseph/Desktop/test.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF) {
            chunk_type = determine_chunk_type(c, previous_c, previous_c_2);
            switch(chunk_type) {
                case 0:
                    // check c value and determine which chunk type
                    break;
                case 1:
                    // handle date, when arrive at space or EOL change chunk to 0
                    break;
                case 2:
                    // handle descr, when arrive at EOL change chunk to 0
                    break;
                case 3:
                    // handle to account, when arrive at space or EOL change chunk to 0
                    break;
                case 4:
                    // handle from account, when arrive at space or EOL change chunk to 0
                    break;
                case 5:
                    // handle amount, when arrive at EOL change chunk to 0
                    break;
                case 6:
                    // handle comment, when arrive at EOL change chunk to 0
                    break;
                default:
                    printf("Error: invalid chunk type");
            }
        
            previous_c_2 = previous_c;
            previous_c = c;
        }
        fclose(file);
    }
    
    return 0;
}

/*
- Read character
- If it is ;, then ignore chars until end of line
- If it is int, then read as date and write to csv
- If it is text following int, then read as descr and write to csv
- If it is text following single space, then read as account and write to csv
- If it is $ followed by two spaces, then read as amount and write to csv
*/
