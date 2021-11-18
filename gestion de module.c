#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define success 100
#define error 33




int ModulenEf = 0;
int ProfesseurnEf = 0;
int EtudiantnEf = 0;


int ModuleNombreEtudiant = 0;
int error404 = 0;
int found = 0;
/* 
#########################################################################################################################
#												LES STRUCTURES 															#
#########################################################################################################################
*/


typedef struct date{
	int j;
	int m;
	int a;
}date;


typedef struct professeur{
	int id;
	int salaire;
	char nom[30];
	char prenom[30];
	char adresse[30];
	char nv_scolaire[30];
	date date_struct;

	
}professeur;


typedef struct etudiant{
	int id;
	int age;
	char nom[30];
	char prenom[30];
	char adresse[30];
	
	struct etudiant * suivant;
	
}etudiant, * etud;

typedef struct module{
	int code;
	char nom_module[30];
	professeur prof;
	etudiant etud;
	date date_launch;
	date expired;
	
	
	struct module * suivant;
	
}module, * mod;



//------------------------------------------ INITIALISATION -------------------------------
mod initModule()
{
	mod m = NULL;
	return m;
}

etud initEtudiant()
{
	etud e = NULL;
	return e;

}
professeur p[100];


//*****************************************************************************************************************************************
// --------------------------------------LES FONCTIONS DE LA PARTIE PROFESSEUR ------------------------------------------------------------

int AddProf(int ID,char nom[],char prenom[],char adresse[],char level[],int salaire,int jD,int moD, int aD)
{
	int i;
	for(i=0;i<ProfesseurnEf;i++)
	{
		if(strcmp(p[i].nom,nom) == 0)
		{
			
			return error;
		}
	}	
	p[ProfesseurnEf].id = ID;
	strcpy(p[ProfesseurnEf].nom,nom);
	strcpy(p[ProfesseurnEf].prenom,prenom);
	strcpy(p[ProfesseurnEf].adresse,adresse);
	strcpy(p[ProfesseurnEf].nv_scolaire,level);
	p[ProfesseurnEf].salaire = salaire;
	p[ProfesseurnEf].date_struct.j = jD;
	p[ProfesseurnEf].date_struct.m = moD ;
	p[ProfesseurnEf].date_struct.a = aD;
	

	
	return success;
	
}

void ShowProf()
{
	if( ProfesseurnEf == 0)
	{
		printf("Il n'existe aucun professeur \n");
		return;
	}
	int i;
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("- 					AFFICHAGE DES PROFESSEURS            	  			 	-\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n\n");
	printf("					[ID]	[NOM]	[PRENOM]    [J][M][A]\n\n");
    for(i=0;i<ProfesseurnEf;i++)
    {
		printf("					[%d]	[%s]	[%s]	    [%d/%d/%d]  \n",p[i].id,p[i].nom,p[i].prenom,p[i].date_struct.j,p[i].date_struct.m,p[i].date_struct.a);
	}


}

mod ModifProfesseur(char nom[], char Nnom[],char module[], mod m)
{
	if( m == NULL)
	{
		return NULL;
	}
	
	if(RechercheModule(module,m) == error)
	{
		return NULL;
	}
	
	while(m != NULL)
	{
		if(strcmp(m->prof.nom,nom) == 0)
		{
			strcpy(m->prof.nom,Nnom);
			return m;
		}
		
		m = m -> suivant;
	}
	return NULL;
}
// -----------------------------------------------------------------------------------------------------------------------------------------------
//*************************************************************************************************************************************************



//***********************************************************************************************************************************************
// -----------------------------------------------------LES FONCTIONS DE LA PARTIE MODULE --------------------------------------------------------

mod AddModule(int code,char name[],char prof[],mod m,int j,int mo,int a,int jF,int moF,int aF)
{
	mod m1, m2;
 
	if( RechercheModule(name,m) == success)
	{
		error404 = 1;
		return m;
	}                 
	
	m1 = malloc(sizeof(module));
	m1->code = code;
	m1->date_launch.j = j;
	m1->date_launch.m = mo;
	m1->date_launch.a = a;
	
	m1->expired.j = jF;
	m1->expired.m = moF;
	m1->expired.a = aF;
	strcpy(m1->nom_module,name);
	strcpy(m1->prof.nom,prof);
	
	m1->suivant = NULL;
	
	if( m == NULL)
	{
		return m1;
	}
	m2 = m;
	while(m2->suivant != NULL)
	{
		m2 = m2 -> suivant;
	}
	m2->suivant = m1;
	return m;
	
}

void ShowList(mod m)
{
	if( ModulenEf == 0)	
	{
		printf("Il n'existe aucun module \n");
		return;
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("- 					AFFICHAGE DES MODULES	            	  			 	-\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n\n");
	printf("					[CODE]	[NOM]     |[PROF]| [J][M][A]	[J][M][A]\n\n");
	while(m != NULL)
    {
      printf("					[%d]	[%s]   |[%s]|    [%d/%d/%d]      [%d/%d/%d] \n ",m->code,m->nom_module,m->prof.nom,m->date_launch.j,m->date_launch.m,m->date_launch.a,m->expired.j,m->expired.m,m->expired.a);
      m = m->suivant;
    }
}

void ShowList10(mod m)
{
	if( ModulenEf == 0)
	{
		printf("Il n'existe aucun module \n");
		return;
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("- 					AFFICHAGE DES MODULES	            	  			 	-\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n\n");
	printf("					[CODE]	[NOM] |[PROF]| [J][M][A]   [J][M][A]\n\n");
	while(m != NULL)
	{
	
		if(m->expired.a - 10 > m->date_launch.a)
    	{
      		printf("					[%d]	[%s]   |[%s]|[%d/%d/%d]   [%d][%d][%d] \n ",m->code,m->nom_module,m->prof.nom,m->date_launch.j,m->date_launch.m,m->date_launch.a,m->expired.j,m->expired.m,m->expired.a);
		}
		m = m->suivant;
	}
}
mod AddEtudModule(char nomEtud[], char nom_module[], mod m,etud e)
{
	int i, indiceEtudiant = 0;
	
	while(e!= NULL && indiceEtudiant == 0)
	{
		if(strcmp(e->nom,nomEtud) == 0)
		{
			indiceEtudiant = 1;
		}
		e = e-> suivant;
	}
	if(indiceEtudiant == 0)
	{
		error404 = 1;
		return m;
	}                           
        strcpy(m->etud.nom,nomEtud);
        ModuleNombreEtudiant++;
	    return m;
     
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//******************************************************************************************************************************************************



//***********************************************************************************************************************************************
// -----------------------------------------------------LES FONCTIONS DE LA PARTIE ETUDIANT --------------------------------------------------------




etud AddEtudiant(int code,char name[],char prenom[], char adresse[], int age, etud e)
{
	etud e1, e2;

	e1 = malloc(sizeof(etudiant));
	e1->id = code;
	e1->age = age;
	strcpy(e1->nom,name);
	strcpy(e1->prenom,prenom);
	strcpy(e1->adresse,adresse);
	
	e1->suivant = NULL;
	
	if( e == NULL)
	{
		return e1;
	}
	e2 = e;
	while(e2->suivant != NULL)
	{
		e2 = e2 -> suivant;
	}
	e2->suivant = e1;
	return e;
}

void ShowEtud(etud e)
{
    if( EtudiantnEf == 0)
	{
		printf("Il n'existe aucun etudiant \n");
		return;
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("- 					AFFICHAGE DES ETUDIANTS	            	  			 	-\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n\n");
	printf("			[ID]		[NOM]		[PRENOM]	[ADRESSE]	[AGE]\n\n");
	while(e != NULL)
    {

    printf("			[%d]		[%s]		[%s]		[%s]	        [%d] \n ",e->id,e->nom,e->prenom,e->adresse,e->age);
		e = e->suivant;
    }
}

void ShowEtud20(etud e)
{
    if( EtudiantnEf == 0)
	{
		printf("Il n'existe aucun etudiant \n");
		return;
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("- 					AFFICHAGE DES ETUDIANTS	            	  			 	-\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n\n");
	printf("			[ID]		[NOM]		[PRENOM]	[ADRESSE]   [AGE]\n\n");	
	while(e != NULL)
	{
	
		if(e->age > 20)
    	{

    		printf("			[%d]		[%s]		[%s]		[%s]         [%d] \n ",e->id,e->nom,e->prenom,e->adresse,e->age);
			
   	 	}
   	 	e = e->suivant;
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
//******************************************************************************************************************************************************




//***********************************************************************************************************************************************
// -----------------------------------------------------LES FONCTIONS DE RECHERCHE --------------------------------------------------------


int RechercheModule(char nom[], mod m)
{
	
	while(m != NULL)
	{
		if(strcmp(m->nom_module,nom) == 0)
		{
			return success;
		}
		
		m = m -> suivant;
	}
	return error;
	
}

int RechercheEtudiant(char nom[],char module[], mod m)
{
	mod m1 = m;
	if(RechercheModule(module,m) == error)
	{
		return error;
	}
		
	while(m1 != NULL)
	{
	
		if(strcmp(m1->etud.nom,nom) == 0)
		{	
			return success;
		}
		
		m1 = m1 -> suivant;
	}
	return error;	
}
int RechercheSOLOPROF(char nom[])
{
    int i;
    for(i=0;i< ProfesseurnEf ; i++)
    {
        if(strcmp(nom,p[i].nom)== 0)
        {
           return success;
        }           
    } 
    
    return error;
    
}
int RechercheProfesseur(char nom[],char module[], mod m)
{
	
	if(RechercheModule(module,m) == error)
	{
		return error;
	}
	
	while(m != NULL)
	{
		if(strcmp(m->prof.nom,nom) == 0)
		{
			return success;
		}
		
		m = m -> suivant;
	}
	return error;	
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//******************************************************************************************************************************************************



//***********************************************************************************************************************************************
// -----------------------------------------------------LES FONCTIONS DE SUPPRESSION ----------------------------------------------------------

mod SuppModule(mod m)
{
	mod m1 = m, m2 = m;
	if(m!= NULL)
	{
		while(m1 -> suivant -> suivant != NULL)
		{
			m1 = m1 -> suivant;
		}
		m2 = m1 -> suivant;
		m1 -> suivant = NULL;
		free(m2);
		return m;
	}
	
	error404 =1;
	return m;
}

mod SuppEtudiant(char nom[], mod m, etud e)
{
	mod m1 = m, m2 = m;
	while(e != NULL)
	{
		if(strcmp(e->nom,nom) == 0)
		{
			found = 1;
			return m;	
		}
		e = e -> suivant;
	}	
}



//------------------------------------------------------------------------------------------------------------------------------------------------------
//******************************************************************************************************************************************************

main()
{
	mod m = initModule();
	int i,found = 0, rep = 0, age;
	etud e = initEtudiant();
	
	int IDe =0, IDp = 0 ,salaire;
	char Nnom[30];
	
	int code,choice;
	int a,mo,j;
	int aF,moF,jF;
	
	
	
	char prof[15],nom[15],prenom[15],module[30],level[10],adresse[30];;
	while(1)
	{
	
	do {

		
		printf("\t\t			---------------------------------------\n");
		printf("\t\t			| -{1} [Ajout]			     -| \n");
		printf("\t\t			| -{2} [Affichage]		     -|\n");
		printf("\t\t			| -{3} [Recherche]		     -|\n");
		printf("\t\t			|-------------------------------------|\n");
		printf("\t\t			| -{4} [Modification / Suppression]  -|\n");
		printf("\t\t			|-------------------------------------|\n");
		printf("\t\t			| -{5}  EXIT	   		     -|\n");
		printf("\t\t			|-------------------------------------|\n");
		printf("\t\t\t\t\t\t\t  ");
		scanf("%d",&choice);
	
		switch(choice)
		{
			do{
			
			case 1:
				system("CLS");
				printf("\t\t			-------------------------------------\n");
				printf("\t\t			| -{1}	Ajout Etudiant	  	   -|\n");
				printf("\t\t			| -{2}	Ajout Professeur	   -|\n");
				printf("\t\t			| -{3}	Ajout Module	  	   -|\n");
				printf("\t\t			| -{4}  Ajout E to Module	   -|\n");
				printf("\t\t			-------------------------------------\n");
				printf("\t\t			| -{5}  EXIT	   		   -|\n");
				printf("\t\t			-------------------------------------\n");
				printf("\t\t\t\t\t\t\t  ");				
				scanf("%d",&choice);
				switch(choice)
				{
					case 1:
						system("CLS");
						IDe++;
						printf("=> ID : %d\n",IDe);
						printf("=> Nom du d'etudiant : ");
						fflush(stdin);
						gets(nom);
						printf("=> Prenom d'etudiant : ");
						fflush(stdin);
						gets(prenom);				
						printf("=> Adresse d'etudiant : ");
						fflush(stdin);
						gets(adresse);
						printf("=> Age : ");
						scanf("%d",&age);
						e = AddEtudiant(IDe,nom,prenom,adresse,age,e);
						if (e != NULL)
						{
							printf("\n\nAjoute avec success \n");
							EtudiantnEf++;
						}
						else
						{
							printf("\n\nErreur d'ajout \n");
							IDe--;
						}
				
						system("PAUSE");
						system("CLS");				
					break;
					case 2:
						system("CLS");
			
						IDp++;
						printf("=> ID : %d\n",IDp);
						printf("=> Nom du Professeur : ");
						fflush(stdin);
						gets(nom);
						printf("=> Prenom du Professeur : ");
						fflush(stdin);
						gets(prenom);				
						printf("=> Adresse du Professeur : ");
						fflush(stdin);
						gets(adresse);
						printf("=> Niveau scolaire : ");
						fflush(stdin);
						gets(level);
						printf("=> Salaire : ");
						scanf("%d",&salaire);
						printf("- Date \n");
						printf("Jour : ");  scanf("%d",&j);
						printf("Mois : ");  scanf("%d",&mo);
						printf("Annee : "); scanf("%d",&a);
						choice = AddProf(IDp,nom,prenom,adresse,level,salaire,j,mo,a);
						if(choice == success)
						{
							printf("\n\nProfesseur ajoute avec success \n");
							ProfesseurnEf++;
						}
						else
						{
							printf("\n\nErreur d'ajout \n");
							IDp--;
						}
						system("PAUSE");
						system("CLS");			
					break;
					case 3:
						system("CLS");
						error404 = 0;
						rep = 0;
						printf("=> Code du Module : ");
						scanf("%d",&code);
						printf("=> Nom du Module : ");
						fflush(stdin);
						gets(module);
						printf("=> La liste des professeurs : \n");
						ShowProf();
						if(ProfesseurnEf == 0)
						{
							system("PAUSE");
							system("CLS");
							continue;
						}
						do{
							printf("=> Nom du Professeur : ");
							gets(nom);
							for(i=0;i<ProfesseurnEf && found == 0;i++)
							{
								if(strcmp(nom,p[i].nom) == 0)
								{
									found = 1;
								}
							}
							if(found == 0)
							{
								printf("\n \n Nom introuvable veuillez ressayer ! \n");
								rep++;
							}
		
						}while(rep <= 3 && found == 0);
						
						if(found == 0 )
						{
							printf("Erreur ! \n");
							system("PAUSE");
							system("CLS");
							continue;					
						}				
						printf("- Date du lancement  \n");
						printf("Jour : ");  scanf("%d",&j);
						printf("Mois : ");  scanf("%d",&mo);
						printf("Annee : "); scanf("%d",&a);

						printf("- Date fin module  \n");
						printf("Jour : ");  scanf("%d",&jF);
						printf("Mois : ");  scanf("%d",&moF);
						printf("Annee : "); scanf("%d",&aF);
						
						m = AddModule(code,module,nom,m,j,mo,a,jF,moF,aF);
						if (m != NULL && error404 == 0)
						{
							printf("\n \nAjoute avec success \n");
							ModulenEf++;
						}
						else
						{
							printf("\n\nErreur d'ajout \n");
						}
						
						system("PAUSE");
						system("CLS");
					break;
					case 4:
						system("CLS");
				
						error404 = 0;
						printf("=> La liste des etudiants : \n\n");
						ShowEtud(e);
						if(EtudiantnEf == 0)
						{
							system("PAUSE");
							system("CLS");
							continue;
						}
						printf("\n\n");
						printf("=> Nom etudiant souhaite : ");
						fflush(stdin);
						gets(nom);
						printf("\n \nLa liste des modules : \n");
						ShowList(m);
						if(ModulenEf == 0)
						{
							system("PAUSE");
							system("CLS");
							continue;
						}
						printf("\n\n");	
						printf("=> Nom du module souhaite : ");
						fflush(stdin);
						gets(module);
						choice = RechercheModule(module,m);
						if(choice == error)
						{
							printf("Le module n'exite pas \n");
							system("PAUSE");
							system("CLS");
							continue;
						}
						m = AddEtudModule(nom,module,m,e);
						if (m != NULL && error404 == 0)
						{
							printf("\n\nAjoute avec success \n");
							ModulenEf++;
						}
						else
						{
							printf("\n\nErreur d'ajout \n");
						}
						system("PAUSE");
						system("CLS");				
	
					break;					
				}
				}while(choice <= 4);
				system("CLS");
				continue;
			case 2:
				do{
				
						system("CLS");
						
						printf("\t\t			| -{1}	Affichage des Etudiants    -|\n");
						printf("\t\t			| -{2}	Affichage des Professeurs  -|\n");
						printf("\t\t			| -{3}	Affichage des Modules 	   -|\n");
						printf("\t\t			| -{4}	 Modules > 10 ans	   -|\n");
						printf("\t\t			-------------------------------------\n");
						printf("\t\t			| -{5}  EXIT	   		   -|\n");
						printf("\t\t			-------------------------------------\n");
						printf("\t\t\t\t\t\t\t  ");						
						scanf("%d",&choice);
				switch(choice)
				{
					case 1:
						system("CLS");
						ShowEtud(e);
						printf("\n\n");
						system("PAUSE");
						system("CLS");				
					break;
					case 2:
						system("CLS");
						ShowProf();
						printf("\n\n");
						system("PAUSE");
						system("CLS");				
					break;
					case 3:
						system("CLS");
						ShowList(m);
						printf("\n\n");
						system("PAUSE");
						system("CLS");
					break;
					case 4:
						system("CLS");
						ShowList10(m);
						printf("\n\n");
						system("PAUSE");
						system("CLS");
					break;
				}
				}while(choice <= 4);
				system("CLS");
				continue;
				
			case 3:
				do{
						system("CLS");

						printf("\t\t			| -{1}	Recherche Etudiants    	   -|\n");
						printf("\t\t			| -{2}	- Etudiants > 20 ans       -|\n");
						printf("\t\t			| -{3}	Recherche Professeurs      -|\n");
						printf("\t\t			| -{4}	Recherche Modules	   -|\n");
						printf("\t\t			-------------------------------------\n");
						printf("\t\t			| -{5}  EXIT	   		   -|\n");
						printf("\t\t			-------------------------------------\n");
						printf("\t\t\t\t\t\t\t  ");						
						scanf("%d",&choice);

				switch(choice)
				{
					case 1:
						system("CLS");
						printf("=> Entrer le module :");
						fflush(stdin);
						gets(module);
						printf("=> Entrer le nom d'etudiant :");
						fflush(stdin);
						gets(nom);
						choice = RechercheEtudiant(nom,module,m);
						if(choice == success)
						{
							printf("\n\nL'etudiant existe ! \n");
						}
						else
						{
							printf("\n\nL'etudiant ou le module n'existe pas \n");
						}
						system("PAUSE");
						system("CLS");
					break;
					case 2:
						ShowEtud20(e);
						printf("\n\n");
						system("PAUSE");
						system("CLS");	
					break;
					case 3:
						system("CLS");

						printf("=> Entrer le module :");
						fflush(stdin);
						gets(module);
						printf("=> Entrer le nom du professeur :");
						fflush(stdin);
						gets(nom);
						choice = RechercheProfesseur(nom,module,m);
						if(choice == success)
						{
							printf("\n\nLe professeur existe ! \n");
						}
						else
						{
							printf("\n\nLe professeur n'existe pas \n");
						}
						system("PAUSE");
						system("CLS");				
					break;
					case 4:
						system("CLS");
	
						printf("=> Entrer le nom du module :");
						fflush(stdin);
						gets(nom);
						choice = RechercheModule(nom,m);
						if(choice == success)
						{
							printf("\n\nLe module existe ! \n");
						}
						else
						{
							printf("\n\nLe module n'existe pas \n");
						}
						system("PAUSE");
						system("CLS");
					break;
				}
				}while(choice <= 4);
				system("CLS");
				continue;
			case 4:
				do{
						system("CLS");
						printf("\t\t			| -{1}  Modifier un Professeur d'un module   -|\n");
						printf("\t\t			| -{2}  Supprimer un Module                  -|\n");
						printf("\t\t			| -{3}  Supprimer un Etudiant                -|\n");
						printf("\t\t			-----------------------------------------------\n");
						printf("\t\t			| -{5}  EXIT	   		             -|\n");
						printf("\t\t			-----------------------------------------------\n");
						printf("\t\t\t\t\t\t\t  ");
						scanf("%d",&choice);
				switch(choice)
				{
					case 1:
						system("CLS");
						printf("=> Entrer le module :");
						fflush(stdin);
						gets(module);
						printf("=> Entrer le nom du professeur :");
						fflush(stdin);
						gets(nom);
						printf("=> Entrer un nouveau nom :");
						fflush(stdin);
						gets(Nnom);
						m = ModifProfesseur(nom,Nnom,module,m);
						if(m != NULL)
						{
							printf("\n\nModification avec success ! \n");
						}
						else
						{
							printf("\n\nErreur de modification \n");
						}	
						system("PAUSE");
						system("CLS");			
					break;
			
					case 2:
						system("CLS");
						error404 = 0;
						m = SuppModule(m);
						if(m!= NULL && error404 == 0)
						{
							printf("\n\nSuppression du dernier module avec success \n\n");
							ShowList(m);
							
						}
						else
						{
							printf("\n\nErreur de suppression \n");	
						}
						
						system("PAUSE");
						system("CLS");					
					break;
					case 3:
						system("CLS");

						found = 0;				
						printf("=> Entrer le module : ");
						fflush(stdin);
						gets(module);
						if(RechercheModule(module,m) == success)
						{
							printf("=> Entrer Le nom d'etudiant a supprimer : ");
							fflush(stdin);
							gets(nom);
					
							m = SuppEtudiant(nom,m,e);
						}
						system("PAUSE");
						system("CLS");					
				
					break;
				}
			}while(choice <= 4);
			system("cls");
			continue;
	case 5:
	return;
	break;
		
	}
}while(choice <= 4);;
	
}
}
