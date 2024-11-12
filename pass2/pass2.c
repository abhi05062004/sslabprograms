#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    char label[10], opcode[10], operand[10], mnemonic[10], symbol[10];
    char start[10], t1[200], a1[10], c1[10], ad[10];
    int address, code, add, len, actual_len, tlen = 0;

    // File pointers for different data files
    FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6;
    fp1 = fopen("assmlist.dat", "w");   
    fp2 = fopen("symtab.dat", "r");     
    fp3 = fopen("intermediate.dat", "r"); 
    fp4 = fopen("optabpass2.dat", "r");      
    fp5 = fopen("objrcd.dat", "w");     
    fp6 = fopen("len.dat", "r");       

    // Initialize empty string for storing object code
    strcpy(t1, "");

    
    fscanf(fp3, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        fprintf(fp1, "\t%s\t%s\t%s\n", label, opcode, operand);
        strcpy(start, operand);
        fscanf(fp6, "%d", &len);  // Read the program length
        fprintf(fp5, "H^%-6s^00%s^0000%d\nT^00%s^", label, operand, len, operand);
        fscanf(fp3, "%d %s %s %s", &address, label, opcode, operand);
        fclose(fp6);
    }

    // Process instructions until END is encountered
    while (strcmp(opcode, "END") != 0) {
        if (strcmp(opcode, "BYTE") == 0) {
            // Handle BYTE opcode (literal data)
            fprintf(fp1, "%d\t%s\t%s\t%s\t", address, label, opcode, operand);
            len = strlen(operand);
            actual_len = len - 3;  // Adjust for 'X' or 'C' prefix

            // Convert byte values to hex and add to object code
            for (int i = 2; i < (actual_len + 2); i++) {
                sprintf(ad, "%X", operand[i]);
                fprintf(fp1, "%s", ad);
                if ((tlen + 2 * actual_len) <= 60) {
                    strcat(t1, ad);
                } else {
                    fprintf(fp5, "%X^%s", tlen / 2, t1);
                    fprintf(fp5, "\nT^00%d", address);
                    tlen = 0;
                    strcpy(t1, "");
                    strcat(t1, ad);
                }
            }
            fprintf(fp1, "\n");
            strcat(t1, "^");
            tlen += 2 * actual_len;

        } else if (strcmp(opcode, "WORD") == 0) {
            // Handle WORD opcode (6-digit numeric literal)
            len = strlen(operand);
            sprintf(a1, "%s", operand);
            fprintf(fp1, "%d\t%s\t%s\t%s\t00000%s\n", address, label, opcode, operand, a1);

            // Add WORD value to object code
            if ((tlen + 6) <= 60) {
                strcat(t1, "00000");
                strcat(t1, a1);
                strcat(t1, "^");
            } else {
                fprintf(fp5, "%X^%s", tlen / 2, t1);
                fprintf(fp5, "\nT^00%d", address);
                tlen = 0;
                strcpy(t1, "");
                strcat(t1, "00000");
                strcat(t1, a1);
                strcat(t1, "^");
            }
            tlen += 6;
        } else if (strcmp(opcode, "RESB") == 0 || strcmp(opcode, "RESW") == 0) {
            // Handle reserved memory (RESB/RESW)
            fprintf(fp1, "%d\t%s\t%s\t%s\n", address, label, opcode, operand);
        } else {
            // Look up the opcode in the operation table
            rewind(fp4);
            fscanf(fp4, "%s%d", mnemonic, &code);
            while (strcmp(opcode, mnemonic) != 0) {
                fscanf(fp4, "%s%d", mnemonic, &code);
            }

            // If operand is a symbol, look up its address in the symbol table
            if (strcmp(operand, "**") == 0) {
                fprintf(fp1, "%d\t%s\t%s\t%s\t%d0000\n", address, label, opcode, operand, code);
            } else {
                rewind(fp2);
                fscanf(fp2, "%s%d", symbol, &add);
                while (strcmp(operand, symbol) != 0) {
                    fscanf(fp2, "%s%d", symbol, &add);
                }
                fprintf(fp1, "%d\t%s\t%s\t%s\t%d%d\n", address, label, opcode, operand, code, add);
                sprintf(c1, "%d", code);
                sprintf(a1, "%d", add);

                // Add to object code
                if ((tlen + 6) <= 60) {
                    strcat(t1, c1);
                    strcat(t1, a1);
                    strcat(t1, "^");
                } else {
                    fprintf(fp5, "%X^%s", tlen / 2, t1);
                    fprintf(fp5, "\nT^00%d", address);
                    tlen = 0;
                    strcpy(t1, "");
                    strcat(t1, c1);
                    strcat(t1, a1);
                    strcat(t1, "^");
                }
                tlen += 6;
            }
        }
        // Read the next instruction
        fscanf(fp3, "%d %s %s %s", &address, label, opcode, operand);
    }
    fprintf(fp5, "%X^%s", tlen / 2, t1);
    fprintf(fp1, "%d\t%s\t%s\t%s\n", address, label, opcode, operand);
    fprintf(fp5, "\nE^00%s", start);
    printf("\nFinished\n");
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
}
