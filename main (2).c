# include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
# define PION_BLANC 1
# define PION_NOIR -1
# define CASE_VIDE 0
//La structure case, qui symbolise une case, elle a donc pour élément deux entiers, un pour la ligne,un autre pour la colonne
typedef struct {
    int lig,col ;
} Case ;
//La structure deplacement, qui symbolise un deplacement, cette structure possède deux éléments,deux case, une étant la case initiale, l’autre la case finale
typedef struct {
    Case case_i,case_f ;
} deplacement ;

//La structure joueur, qui symbolise un joueur, elle a pour élément le nom du joueur ainsi que la couleur des pions du joueurs :
typedef struct {
    char *nom ;
    int couleur ;
} joueur ;

typedef struct {
    int plateau[8][8] ; // Représente l’état du plateau
    char  c; // Représente le le couleur de la cas
} damier ;


void affiche(int** p){
    int i,j;
    for (i=0;i<8;i++){
        for (j=0;j<8;j++){
            printf("%d  ",p[i][j]);
        }printf("\n");
    }
}

char couleur(int i,int j){
    return ((i+j)%8)+65;
}
// une Procedure qui permet d'afficher le contenu d'une Ligne 
void affiche_ligne(int i,int** p) {
    int k,j ;
    printf(" %d ",i+1) ;
    for(j=0 ;j<8 ;j++) {
        if(p[i][j]==0){ 
                printf("| O%c",couleur(i,j)) ;
        }
        else if(p[i][j]==1){
                printf("| X%c",couleur(i,j)) ;
        }
        else if(p[i][j]==-1) {
            
               printf("| Y%c",couleur(i,j)) ;
        }
    }
    printf("| %d\n",i+1) ;
    printf(" |---------------------------------|\n") ;
}

//une Procedure qui Permet d'afficher toute le Plateau 
void affiche_damier(int** p) {
    int i ;
    printf("    a   b   c   d   e   f   g   h \n") ;
    printf(" |---------------------------------|\n") ;
        for(i=0 ;i<8 ;i++){
            affiche_ligne(i,p) ;
        }
        printf("    a   b   c   d   e   f   g   h \n") ;
    }
    
//Pour initialiser, le damier, il suffit de donner la valeur PION NOIR et PION BLANC aux cases où les pions doivent se trouver en début de partie.
void init_damier(int **p) {
    int i,j ;
        printf("Damier a l'etat brut \n");
        affiche_damier(p);  
        //On remplie le Premier Ligne de la partie haute du damier par des pions noirs
        for(j=0 ;j<8 ;j++){
            p[0][j] = PION_BLANC;
        }
        // on parcours la partie entre la deuxieme ligne et l'avant derniere ligne en gardant les cases vides
        for(i=1 ;i<7 ;i++){
            for(j=0 ;j<8 ;j++){
                p[i][j]=CASE_VIDE;
            }
        }
        //On remplie le Premier Ligne de la partie basse du damier par des pions blancs
        for(j=0 ;j<8 ;j++){
            p[7][j] = PION_NOIR ;
        }

    printf("Damier a l'etat initial \n");
    affiche_damier(p);    
    }


//verifier es que une Mouvement horizontal est possible
bool possible_horizontale(deplacement d,int **p){
    int i_d,i_f,j_d,j_f;
    int i,j,a,b,aux;
    bool test;
    j_d=d.case_i.col;
    j_f=d.case_f.col;
    i_d=d.case_i.lig;
    if (j_f<j_d){
        aux=j_d;
        j_d=j_f;
        j_f=aux;
    }
    test=true;
    for (j=j_d+1; j<=j_f;i++){
        if (p[i][j]!=CASE_VIDE){
            test=false;
        }
    }
    return test;
}
// verifier si une deplacement horizentale est permis 
bool permis_horizontal(deplacement d,int **p){
    int i_d,i_f,j_d,j_f,i,j;
    j_d=d.case_i.col;
    j_f=d.case_f.col;
    i_d=d.case_i.lig;
    if ((j_d!=j_d) && (i_d==i_f)){
        return possible_horizontale(d,p);
    }
    else {
        return false;
    }
}

//verifier es que une Mouvement vers le bas est possible
bool possible_vers_le_bas(deplacement d,int **p){
    int i_d,i_f,j_d,j_f,i,j;
    j=d.case_i.col;
    i_d=d.case_i.lig;
    i_f=d.case_f.lig;
    for (i=i_d+1; i<=i_f;i++){
        if (p[i][j]!=CASE_VIDE){
            return false;
        }
    }
    return true;
}
//verifier es que une Mouvement vers le haut est possible
bool possible_vers_le_haut(deplacement d,int **p){
    int i_d,i_f,j_d,j_f,i,j;
    j=d.case_i.col;
    i_d=d.case_i.lig;
    i_f=d.case_f.lig;
    for (i=i_d+1; i<=i_f;i--){
        if (p[i][j]!=CASE_VIDE){
            return false;
        }
    }
    return true;
}


// verifier si une deplacement vers le bas est permis 
bool permis_avant(deplacement d,int **p){
     int i_d,i_f,j_d,j_f,i,j;
    j_d=d.case_i.col;
    j_f=d.case_f.col;
    i_d=d.case_i.lig;
    i_f=d.case_f.lig;
   
    if ((i_d<i_f) && (j_d==j_f)){
        return possible_vers_le_bas(d,p);
    }
    else {
        return false;
    }
}

// verifier si une deplacement vers le haut est permis 
bool permis_haut(deplacement d,int **p){
     int i_d,i_f,j_d,j_f,i,j;
    j_d=d.case_i.col;
    j_f=d.case_f.col;
    i_d=d.case_i.lig;
    i_f=d.case_f.lig;
   
    if ((i_d>i_f) && (j_d==j_f)){
        return possible_vers_le_haut(d,p);
    }
    else {
        return false;
    }
}


//verifier es que une Mouvement diag principale vers le bas est possible
bool possible_vers_le_diag1_bas(deplacement d,int **p){
     int i_d,i_f,j_d,j_f,i,j;
    j_d=d.case_i.col;
    j_f=d.case_f.col;
    i_d=d.case_i.lig;
    i_f=d.case_f.lig;
    i=i_d;
    j=j_d;
    do{
        i=i+1;
        j=j+1;
        if (p[i][j]!=CASE_VIDE){
            return false;
        }
        
        }while ((i>=i_f)||(j>=j_f));
    return true;
}

//verifier es que une Mouvement diag principale vers le haut est possible
bool possible_vers_le_diag1_haut(deplacement d,int **p){
     int i_d,i_f,j_d,j_f,i,j;
    j_d=d.case_i.col;
    j_f=d.case_f.col;
    i_d=d.case_i.lig;
    i_f=d.case_f.lig;
    i=i_d;
    j=j_d;
    do{
        i=i-1;
        j=j-1;
        if (p[i][j]!=CASE_VIDE){
            return false;
        }
        
        }while ((i<=i_f)||(j<=j_f));
    return true;
}
// verifier si une deplacement vers le diag principale vers le bas est permis 
bool permis_diag1_bas(deplacement d,int **p){
    int i_d,i_f,j_d,j_f,i,j;
    j_d=d.case_i.col;
    j_f=d.case_f.col;
    i_d=d.case_i.lig;
    i_f=d.case_f.lig;
    if ((i_d>i_f) && (i_d-j_d==i_f-j_f)){
        return possible_vers_le_diag1_bas(d,p);
    }
    else{
        return false;
    }
}

// verifier si une deplacement vers le diag principale vers le haut est permis 
bool permis_diag1_haut(deplacement d,int **p){
    int i_d,i_f,j_d,j_f,i,j;
    j_d=d.case_i.col;
    j_f=d.case_f.col;
    i_d=d.case_i.lig;
    i_f=d.case_f.lig;
    if ((i_d>i_f) && (i_d-j_d==i_f-j_f)){
        return possible_vers_le_diag1_haut(d,p);
    }
    else{
        return false;
    }
}

//verifier es que une Mouvement diag secondaire vers le bas est possible
bool possible_vers_le_diag2_bas(deplacement d,int **p){
    int i_d,i_f,j_d,j_f,i,j;
    j_d=d.case_i.col;
    j_f=d.case_f.col;
    i_d=d.case_i.lig;
    i_f=d.case_f.lig;
    do{
        i=i+1;
        j=j-1;
        if (p[i][j]!=CASE_VIDE){
            return false;
        }
        
        }while ((i>=i_f)||(j<=j_f));
    return true;
}

//verifier es que une Mouvement diag secondaire vers le haut est possible
bool possible_vers_le_diag2_haut(deplacement d,int **p){
    int i_d,i_f,j_d,j_f,i,j;
    j_d=d.case_i.col;
    j_f=d.case_f.col;
    i_d=d.case_i.lig;
    i_f=d.case_f.lig;
    do{
        i=i-1;
        j=j+1;
        if (p[i][j]!=CASE_VIDE){
            return false;
        }
        
        }while ((i<=i_f)||(j>=j_f));
    return true;
}

// verifier si une deplacement vers le diag secondaire vers le bas est permis 
bool permis_diag2_bas(deplacement d,int **p){
    int i_d,i_f,j_d,j_f,i,j;
    j_d=d.case_i.col;
    j_f=d.case_f.col;
    i_d=d.case_i.lig;
    i_f=d.case_f.lig;
    if ((i_d<i_f) && (j_f-j_d==i_d-i_f)){
        return possible_vers_le_diag1_bas(d,p);
    }
    else {
        return false;
    }
}

// verifier si une deplacement vers le diag secondaire vers le haut est permis 
bool permis_diag2_haut(deplacement d,int **p){
    int i_d,i_f,j_d,j_f,i,j;
    j_d=d.case_i.col;
    j_f=d.case_f.col;
    i_d=d.case_i.lig;
    i_f=d.case_f.lig;
    if ((i_d>i_f) && (j_f-j_d==i_d-i_f)){
        return possible_vers_le_diag1_haut(d,p);
    }
    else {
        return false;
    }
}
// une Fonction qui permet de retourner le choix d'un joueur
Case choisir(){
    Case c;
    do{
    printf("Lignes :\n");
    scanf(" %d",&c.lig);
    printf("colonne :\n");
    scanf(" %d",&c.col);
    }while (!((0<=c.lig<8) && (0<=c.col<8)));
    return c;
}

bool possible_joueur_1(deplacement d,int **p){
    return (possible_horizontale(d,p) || (possible_vers_le_bas(d,p)) || (possible_vers_le_diag1_bas(d,p)) || (possible_vers_le_diag2_bas(d,p)) );
}

//le Premier depplacement du premier Joueur
Case jeux_joueur_x(int **p){
    deplacement d;
    Case cd,cf;
    int i,j;
    do{
    printf("choisir le pion a deplacer parmi les X\n");
    cd=choisir();
    }while(p[cd.lig][cd.col]!=PION_BLANC);
    d.case_i=cd;
    do{
    printf("OU voulez vous deplacer le pion X\n");
    cf=choisir();
    d.case_f=cf;
    }while((p[cf.lig][cf.col]!=CASE_VIDE) && (possible_joueur_1(d,p)));
        p[cd.lig][cd.col]=CASE_VIDE;
        p[cf.lig][cf.col]=PION_BLANC;
  affiche_damier(p);  
  return cf;
}



bool Possible_joueur_2(deplacement d,int **p){
    return ((possible_horizontale(d,p)) || (possible_vers_le_haut(d,p)) || (possible_vers_le_diag1_haut(d,p)) || (possible_vers_le_diag2_haut(d,p))) ;
}
//saisir les noms de deux Joueurs
void saisir_nom(joueur j1,joueur j2){
  printf("donner le nom du Premier de Joeur : \n");
    scanf(" %s",j1.nom);
    printf("donner le nom du Deuxieme de Joeur : \n");
    scanf(" %s",j2.nom);
}
// et que le Jeux Commence
int jeux(int **p){
    deplacement d;
    Case cd,cf;
    joueur j1;
    joueur j2;
    int i,j,tour;
    //saisie de nom des deux Joueur
    saisir_nom(j1,j2);
    //le premier joueur n'a pas le contrainte de couleur
    cf=jeux_joueur_x(p);
    //c'est le tour de deuxieme Joueur
    tour=2;
    // on commence un jeux qui ne s'arrete que lorsque l'un arrive au terrain de l'autre
    while (((tour==2) && (cf.lig!=7)) ||((tour==1) && (cf.lig!=0))){
    if (tour==2){
        //si c'est le deuxieme joueur il choisi un pion de meme couleur que celui ou se trouve le dernier pion de joueur 1
        do{
            printf("choisir le pion a deplacer parmi les Y\n");
            cd=choisir();
        }while((p[cd.lig][cd.col]!=PION_NOIR) || (couleur(cd.lig,cd.col)!=couleur(cf.lig,cf.col)));
        d.case_i=cd;
        //puis il choisi un position legal
        do{
            printf("OU voulez vous deplacer le pion Y\n");
            cf=choisir();
            d.case_f=cf;
        }while ((p[cf.lig][cf.col]!=CASE_VIDE) || (Possible_joueur_2(d,p)==false));
        //on realise le deplacement
        p[cd.lig][cd.col]=CASE_VIDE;
        p[cf.lig][cf.col]=PION_NOIR;
    //puis on affiche la nouvelle etat
    affiche_damier(p); 
    }
    //si c'est le premier joueur il choisi un pion de meme couleur que celui ou se trouve le dernier pion de joueur 2
    else{
       do{
            printf("choisir le pion a deplacer parmi les X\n");
            cd=choisir();
        }while((p[cd.lig][cd.col]!=PION_BLANC) || (couleur(cd.lig,cd.col)!=couleur(cf.lig,cf.col)));
        d.case_i=cd;
        //puis il choisi un position legal
        do{
            printf("OU voulez vous deplacer le pion Y\n");
            cf=choisir();
            d.case_f=cf;
        }while ((p[cf.lig][cf.col]!=CASE_VIDE) || (possible_joueur_1(d,p)==false));
        //on realise le deplacement
        p[cd.lig][cd.col]=CASE_VIDE;
        p[cf.lig][cf.col]=PION_BLANC;
    //puis on affiche la nouvelle etat
    affiche_damier(p); 
    }
    }
    if (cf.lig==0){
        printf("Bravo %s vous avez gagner",j1.nom);
    }
    else{
       printf("Bravo %s vous avez gagner",j2.nom); 
    }
}

int main()
{
    int plateau[8][8];
    int **p;
    Case c1,c2;
    joueur j1,j2;
    int i;
    p=(malloc (8*sizeof(int *)));
    for (i=0 ;i<8 ;i++){
        p[i]=malloc(8*sizeof(int));
    }
    init_damier(p);
    jeux(p);
    return 0;
}






