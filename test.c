#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void display() {
    int str;  // Changed from char to int
    FILE *f1, *f2, *f3;
    
    f1 = fopen("input.txt", "r");    
    printf("Contents of input.txt:\n");
    while ((str = fgetc(f1)) != EOF) {
        printf("%c", (char)str);
    }
    fclose(f1);
    
    f2 = fopen("intermediate.txt", "r");
    printf("\nContents of intermediate.txt:\n");
    while ((str = fgetc(f2)) != EOF) {
        printf("%c", (char)str);
    }
    fclose(f2);
    
    f3 = fopen("symtab.txt", "r");
    printf("\nContents of symtab.txt:\n");
    while ((str = fgetc(f3)) != EOF) {
        printf("%c", (char)str);
    }
    fclose(f3);
}

void main(){
    char label[100], opcode[100], operand[100], code[100], mnemonoc[100];
    int locctr, start, length;
    FILE *f1, *f2, *f3, *f4, *f5;
    f1 = fopen("input.txt", "r");
    f2 = fopen("optab.txt", "r");
    f3 = fopen("intermediate.txt", "w");
    f4 = fopen("symtab.txt", "w");
    f5 = fopen("length.txt", "w");
    fscanf(f1, "%s\t%s\t%s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        sscanf(operand, "%x", &start);
        locctr = start;
        fprintf(f3, "\t%s\t%s\t%s\n", label, opcode, operand);
    }
    else 
        locctr = 0;
    while(strcmp(opcode, "END") != 0){
        fprintf(f3, "%x\t%s\t%s\t%s", locctr, label, opcode, operand);
        if(strcmp(label, "**") != 0){
            fprintf(f4, "%s\t%x", label, locctr);
        }
        rewind(f2);  // Reset OPTAB file position before each search
        fscanf(f2, "%s\t%s", code, mnemonoc);
        while(strcmp(code, "END") != 0){
            if(strcmp(code, opcode) == 0){
                locctr += 3;
                break;
            }
            fscanf(f2, "%s\t%s", code, mnemonoc);
        }
        if(strcmp(opcode, "WORD") == 0)
            locctr += 3;
        else if(strcmp(opcode, "RESW") == 0)
            locctr += (3 * atoi(operand));
        else if(strcmp(opcode, "RESB") == 0)
            locctr += atoi(operand);
        else if(strcmp(opcode, "BYTE") == 0)
            locctr += 1;
        fscanf(f1, "%s\t%s\t%s", label, opcode, operand);
    }
    fprintf(f3, "%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    
    display();
    
    length = locctr - start;
    fprintf(f5, "%xH\n", length);
    fclose(f5);
    printf("Length of code: %xH", length);
}