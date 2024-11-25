#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
//flobaillien

struct participant
{
    char NomJoueur[30];
    char sexe;
    char Nationalite[30];
    int NumRenc;
    char resultat[12];
};

struct ind
{
    char NomJoueur[30];
    char sexe;
    int NumRenc;
    int GP;
    long posi;
    struct ind* psvt;
};

void Chargement_nomF1(char *nom_F1);
void Creer_nomF3(char *nom_F3);
void Creer_nomF2(char *nom_F2);

void Mettre_nomF2_nomF3(char *nom_F1, char *nom_F2, char *nom_F3);
void Affiche(char *nom);
void Creation_LLU(char *nom_F2, char *nom_F3,struct ind **index);
void Insertion_LLU(struct ind **index,struct ind *nouv);

void Affiche_LLU(struct ind *index);
void Jeux(struct ind *index);
void Tirage(int tab[4]);
void Creer_nomF4(char *nom_F4);
void Score_F2_F3(char *nom_F2,char *nom_F3,struct ind *index);
void MAJ_F2_F3(char *nom_F2,char *nom_F3,char *nom_F4,struct ind *index);
void Affiche_Podium(char *nom);

int main()
{
    struct ind *index=NULL;

    char nom_F1[]="Roland_Garros.dat";
    char nom_F2[]="RG_Homme.dat";
    char nom_F3[]="RG_Femme.dat";
    char nom_F4[]="PODIUM.dat";

    srand(time(NULL));
    Chargement_nomF1(nom_F1);
    Affiche(nom_F1);
    Creer_nomF2(nom_F2);
    Creer_nomF3(nom_F3);
    Mettre_nomF2_nomF3(nom_F1, nom_F2,nom_F3);
    Affiche(nom_F2);
    Affiche(nom_F3);
    Creation_LLU(nom_F2,nom_F3,&index);
    Affiche_LLU(index);
    Jeux(index);
    Creer_nomF4(nom_F4);
    MAJ_F2_F3(nom_F2,nom_F3,nom_F4,index);
    Affiche_Podium(nom_F4);
    printf("\n_flobaillien_\n");
    return 0;
}
void Chargement_nomF1(char *nom_F1)
{
    FILE *fp1=NULL;
    fp1 = fopen(nom_F1,"r");
    if(!fp1)
    {
        printf("\nLe fichier  'Roland_Garros.dat'  n existe pas \n");
        getch();
    }
    else
    {
        printf("\nAffichage sequentielle du fichier 'Roland_Garros.dat'\n");
    }
}
void Creer_nomF2(char *nom_F2)
{
    FILE *fp2=NULL;
    fp2=fopen(nom_F2,"r");
    fclose(fp2);
    printf("Fichier  'RG_Homme.dat'  a ete creer avec succes\n");
    getch();
}
void Creer_nomF3(char *nom_F3)
{
    FILE *fp3=NULL;
    fp3=fopen(nom_F3,"r");
    fclose(fp3);
    printf("Fichier  'RG_Femme.dat'  a ete creer avec succes\n");
    getch();
}
void Tirage(int tab[4])
{
    int i=0,x;
    while(i<4)
    {
        x = 1 + rand() % 4;
        if(tab[0]!=x)
        {
            if(tab[1]!=x)
            {
                if(tab[2]!=x)
                {
                    if(tab[3]!=x)
                    {
                        tab[i]=x;
                        i++;
                    }
                }
            }
        }
    }
    for(i=0;i<4;i++)
    {
        printf("%4d",tab[i]);
    }
    printf("\n");
}
void Mettre_nomF2_nomF3(char *nom_F1, char *nom_F2, char *nom_F3)
{
    int i,x=0,y=0;
    FILE *fp1=NULL;
    fp1=fopen(nom_F1,"rb");
    int tabH[4];
    Tirage(tabH);
    srand(time(NULL));
    int tabF[4];
    Tirage(tabF);
    struct participant PART;

    FILE *fp2=NULL;
    fp2=fopen(nom_F2,"wb");
    FILE *fp3=NULL;
    fp3=fopen(nom_F3,"wb");

    fread(&PART,sizeof(struct participant),1,fp1);

    for(i=0;i<8;i++)
    {

        if('H'== PART.sexe)
        {
            PART.NumRenc=tabH[x];
            fwrite(&PART,sizeof(struct participant),1,fp2);
            x++;
        }
        else
        {
            PART.NumRenc=tabF[y];
            fwrite(&PART,sizeof(struct participant),1,fp3);
            y++;
        }
        fread(&PART,sizeof(struct participant),1,fp1);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}
void Affiche(char *nom)
{
    int i=1;
    FILE *fp=NULL;
    struct participant PART;
    fp = fopen(nom,"rb");

    fread(&PART,sizeof(struct participant),1,fp);
    printf("\t\t   NOM \t\tSEXE \tNATION. \tNUMRENC\t RESULTAT\n");
    printf("==================================================================\n");
    while(!feof(fp))
    {
        printf("  Joueur %d:\t",i);
        printf("%12s\t",PART.NomJoueur);
        printf("%2c\t",PART.sexe);
        printf("%10s\t",PART.Nationalite);
        printf("%d\t",PART.NumRenc);
        printf("%s\t",PART.resultat);
        printf("\n____________________________________________________________________________________\n");
        getch();
        fread(&PART,sizeof(struct participant),1,fp);
        i++;
    }
    fclose(fp);
}
void Insertion_LLU(struct ind **index,struct ind *nouv)
{
    struct ind *pcour=NULL, *pprec=NULL;
    if(*index == NULL)
    {
        *index = nouv;
    }
    else
    {
        pcour= *index;
        while((nouv->NumRenc>pcour->NumRenc)&&(pcour->psvt != NULL))
        {
            pprec = pcour;
            pcour = pcour->psvt;
        }
        if(pcour == *index && (nouv->NumRenc<=pcour->NumRenc))
        {
            nouv->psvt=*index;
            *index=nouv;
        }
        else
        {
            if(pcour->psvt == NULL && (nouv->NumRenc>pcour->NumRenc))
            {
                pcour->psvt = nouv;
            }
            else
            {
                nouv->psvt = pcour;
                pprec->psvt = nouv;
            }
        }
    }
}
//flo
void Creation_LLU(char *nom_F2, char *nom_F3,struct ind **index)
{
    int pos;
    struct ind *nouv;
    struct participant PART;
    FILE *fp2=NULL;
    FILE *fp3=NULL;
    fp2 = fopen(nom_F2,"r+b");

    pos=1;
    fread(&PART,sizeof(struct participant),1,fp2);
    while(!feof(fp2))
    {
        nouv=(struct ind *)malloc(sizeof(struct ind));
        if(!nouv)
        {
            printf("\nPAS");
            exit(1);
        }
        else
        {
            strcpy(nouv->NomJoueur,PART.NomJoueur);
            nouv->sexe=PART.sexe;
            nouv->NumRenc=PART.NumRenc;
            nouv->posi=pos;
            nouv->psvt=NULL;

            Insertion_LLU(index,nouv);
        }
        fread(&PART,sizeof(struct participant),1,fp2);
        pos++;
    }
    fclose(fp2);

    fp3 = fopen(nom_F3,"r+b");

    pos=1;
    fread(&PART,sizeof(struct participant),1,fp3);
    while(!feof(fp3))
    {
        nouv=(struct ind *)malloc(sizeof(struct ind));
        if(!nouv)
        {
            printf("\nPAS");
            exit(1);
        }
        else
        {
            strcpy(nouv->NomJoueur,PART.NomJoueur);
            nouv->sexe=PART.sexe;
            nouv->NumRenc=PART.NumRenc;
            nouv->posi=pos;
            nouv->psvt=NULL;

            Insertion_LLU(index,nouv);
        }
        fread(&PART,sizeof(struct participant),1,fp3);
        pos++;
    }
}
//flo
void Affiche_LLU(struct ind *index)
{
    printf("\nLLU:");
    while(index)
    {
        printf("\n--------------------------");
        printf("\nNOM:%s",index->NomJoueur);
        printf("\nNumRenc:%d",index->NumRenc);
        index = index->psvt;
    }
    getch();
}
void Jeux(struct ind *index)
{
    int x;
    printf("\n\nLancement des jeux:");
    while(index)
    {
        printf("\n--------------------------");
        printf("\nNOM:%s",index->NomJoueur);
        printf("\nNumRenc:%d",index->NumRenc);
        x = rand() % 2;

        index->GP=x;
        printf("\nGP:%d",index->GP);
        index = index->psvt;

        if(x==1)
        {
            printf("\nNOM:%s",index->NomJoueur);
            printf("\nNumRenc:%d",index->NumRenc);
            index->GP=0;
            printf("\nGP:%d",index->GP);
        }
        else
        {
            if(x==0)
            {
                printf("\nNOM:%s",index->NomJoueur);
                printf("\nNumRenc:%d",index->NumRenc);
                index->GP=1;
                printf("\nGP:%d",index->GP);
            }
        }
    index = index->psvt;
    }
    printf("\n\n");
}
void Creer_nomF4(char *nom_F4)
{
    FILE *fp4=NULL;
    fp4=fopen(nom_F4,"r");
    fclose(fp4);
    printf("Fichier  'PODIUM.dat'  a ete creer avec succes\n");
    getch();
}
//baillien
void MAJ_F2_F3(char *nom_F2,char *nom_F3,char *nom_F4,struct ind *index)
{
    struct participant PART;
    int i;
    char G[12]={"GAGNE      "};
    char P[12]={"PERDU      "};
    char x[12];
    FILE *fp4=NULL;
    fp4=fopen(nom_F4,"wb");

    while(index)
    {
        FILE *fp2=NULL;
        fp2=fopen(nom_F2,"rb");
        FILE *fp3=NULL;
        fp3=fopen(nom_F3,"rb");

        for(i=0;i<8;i++)
        {
            if(index->GP == 1)
            {
                strcpy(x,G);
            }
            else
            {
                strcpy(x,P);
            }
            if(index->sexe == 'H')
            {
                fread(&PART,sizeof(struct participant),1,fp2);

                if(strcmp(index->NomJoueur,PART.NomJoueur) == 0)
                {
                    strcpy(PART.resultat,x);
                    fwrite(&PART,sizeof(struct participant),1,fp4);
                    i = 9;
                }
            }
            if(index->sexe == 'F')
            {
                fread(&PART,sizeof(struct participant),1,fp3);

                if(strcmp(index->NomJoueur,PART.NomJoueur) == 0)
                {
                    strcpy(PART.resultat,x);
                    fwrite(&PART,sizeof(struct participant),1,fp4);
                    i = 9;
                }
            }

        }
        index = index->psvt;
        fclose(fp2);
        fclose(fp3);
    }
    fclose(fp4);
}
void Affiche_Podium(char *nom)
{
    int i=1;
    FILE *fp=NULL;
    struct participant PART;
    fp = fopen(nom,"rb");

    fread(&PART,sizeof(struct participant),1,fp);
    printf("NUMRENC  \t\tNOM \tSEXE   \tNATION.     RESULTAT\n");
    printf("==================================================================\n");
    while(!feof(fp))
    {
        printf("Num Renc: %d\t",PART.NumRenc);
        printf("%12s\t",PART.NomJoueur);
        printf("%2c\t",PART.sexe);
        printf("%10s\t",PART.Nationalite);
        printf("%s\t",PART.resultat);
        printf("\n____________________________________________________________________________________\n");
        getch();
        fread(&PART,sizeof(struct participant),1,fp);
        i++;
    }
    fclose(fp);
}
