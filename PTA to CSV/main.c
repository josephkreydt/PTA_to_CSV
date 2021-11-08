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
 - description is after_a_transaction_status_symbol and goes until EOL
 - comment is after_a_semi-colon and goes until EOL
 - stock amount is after_double_space and goes until end of dollar amount or EOL
*/

int main(int argc, const char * argv[]) {
    int c;
    int previous_c = 0;
    //char delimiter = ",";
    int mode = 0;
    // 0 = no mode
    // 1 = comment mode
    // 2 = description mode
    // 3 = dollar mode
    // 4 = stock mode

    FILE *text_file;
    FILE *csv_file;
    text_file = fopen("/Users/joseph/Desktop/ledger.txt", "r");
    csv_file = fopen("/Users/joseph/Desktop/ledger.csv", "w");
    if (text_file) {
        while ((c = getc(text_file)) != EOF) {
            switch (mode) {
                case 0:
                    // no mode
                    if (c == 32 && previous_c == 32) {
                        // switch to stock mode
                        mode = 4;
                    } else if (c == 32 && previous_c == 42 /*asterisk*/){
                        // switch to descr mode
                        fprintf(csv_file, ",");
                        mode = 2;
                        //printf(c);
                    } else if (c == 59 /*semi-colon*/) {
                        // switch to comment mode
                        mode = 1;
                    } else if (c == 32 && previous_c != 10){
                        fprintf(csv_file, ",");
                    } else if (c == 32 && previous_c == 10 /*line feed*/) {
                        //fprintf(csv_file, ",");
                    } else if (c == 10 && previous_c == 10) {
                        //fprintf(csv_file, "\n");
                    } else if (c == 10 && previous_c == 32) {
                        
                    } else {
                        fprintf(csv_file, "%c", c);
                    }
                    break;
                case 1:
                    // comment mode
                    if (c == 10 /*line feed*/) {
                        mode = 0;
                    } else {
                        // uncomment following line to write comments
                        //fprintf(csv_file, "%c", c);
                    }
                    break;
                case 2:
                    // description mode
                    if (c == 10) {
                        mode = 0;
                        fprintf(csv_file, ",");
                    } else {
                        fprintf(csv_file, "%c", c);
                    }
                    break;
                case 3:
                    // dollar mode
                    if (c == 10 || c == 32) {
                        mode = 0;
                        fprintf(csv_file, ",");
                    } else {
                        fprintf(csv_file, "%c", c);
                    }
                    break;
                case 4:
                    // stock mode
                    if (c == 36 /*dollar sign*/) {
                        fprintf(csv_file, "%c", c);
                        mode = 3;
                    } else {
                        fprintf(csv_file, "%c", c);
                    }
                    break;
                default:
                    fprintf(csv_file, "Error: invalid mode.");
            }
            previous_c = c;
        }
        fclose(text_file);
        fclose(csv_file);
    }
    
    return 0;
}

// KREYDT
