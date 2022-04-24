#include <stdio.h>
#include "lenaArray.h"

/*
    donker naar licht (ASCII waarden in decimaal)
    Tekens:     Grijswaarde:       Case:
    @ = 64      231 - 255           1
    % = 37      200 - 230           2
    # = 35      171 - 199           3
    * = 42      142 - 170           4
    + = 43      113 - 141           5
    = = 61      85 - 112            6
    - = 45      56 - 84             7
    : = 58      29 - 55             8
    . = 46      0 - 28              9

    Grijswaarden min 0 en max 255
    9 tekens dus 255/9 = +- 28 per teken
*/

char grijswaardeNaarTeken(int grijswaarde);

int main(){
    FILE *lenaTekens;       //volledige plaatje in tekens
    FILE *Lena_klein;       //kleinde plaatje in tekens
    FILE *lena1;            //grijswaarden in .txt file
    FILE *lenaGespiegeld;   //gespiegelde plaatje in tekens         
    int totaleGrijswaarde = 0;
    int gemiddeldeGrijswaarde;
    char string;

    lena1 = fopen("lena.txt", "r");
    for(int i = 0; i < (512*512); i++){
        int y, x, grijswaarde;
        fscanf(lena1, "%d\t%d\t%d", &y, &x, &grijswaarde);
        lena[(y-1)][(x-1)] = grijswaarde;
    }
    fclose(lena1);
    
    //Bereken gemiddelde grijswaarde, zet de grijswaarde om in teken en print deze in een .txt (volledige plaatje)
    lenaTekens = fopen("lenaTekens.txt", "w");
    for(int y = 0; y < 512; y++){
        for(int x = 0; x < 512; x++){
            totaleGrijswaarde += lena[y][x];
            char teken = grijswaardeNaarTeken(lena[y][x]);
            fprintf(lenaTekens, " %c", teken);
        }
        fprintf(lenaTekens, "\n");
    }
    fclose(lenaTekens);

    //Bereken gemiddelde grijswaarde, zet de grijswaarde om in teken en print deze in een .txt (kleine plaatje)
    printf("Totale grijswaarde: %d\n",totaleGrijswaarde);
    gemiddeldeGrijswaarde = totaleGrijswaarde / (512*512);
    printf("De gemiddelde grijswaarde van het volledige plaatje is: %d\n", gemiddeldeGrijswaarde);

    totaleGrijswaarde = 0;
    gemiddeldeGrijswaarde = 0;

    //Maak een subset van lena[512][512] waarbij alle rijen en kolommen tussen de 100 en 400 zitten  
    Lena_klein = fopen("Lena_klein.txt", "w");
    for(int y = 100; y < 400; y++){
        for(int x = 100; x < 400; x++){
            lenaSubset[(y-100)][(x-100)] = lena[y][x]; 
            totaleGrijswaarde += lenaSubset[(y-100)][(x-100)];
            char teken = grijswaardeNaarTeken(lena[y][x]);
            fprintf(Lena_klein, "%c", teken);
        }          
        fprintf(Lena_klein, "\n");
    }
    fclose(Lena_klein);

    //Bereken gemiddelde grijswaarde van het kleine plaatje
    printf("Totale grijswaarde van het kleine plaatje is: %d\n", totaleGrijswaarde);
    gemiddeldeGrijswaarde = totaleGrijswaarde / (300*300);
    printf("De gemiddelde grijswaarde van het kleine plaatje is: %d\n", gemiddeldeGrijswaarde);

    lenaGespiegeld = fopen("lenaGespiegeld.txt", "w");
    for(int y = 0; y < 512; y++){
        for(int x = 512; x > 0; x--){
            char teken = grijswaardeNaarTeken(lena[y][x]);
            fprintf(lenaGespiegeld, " %c", teken);
        }
        fprintf(lenaGespiegeld, "\n");
    }
    fclose(lenaGespiegeld);

    return 0;
}

char grijswaardeNaarTeken(int grijswaarde){
    int grijswaardeCase = grijswaarde/28;
    char tekens[10] = {'.','@', '%', '#', '*', '+', '=', '-', ':', '.'};
    return tekens[grijswaardeCase];
}