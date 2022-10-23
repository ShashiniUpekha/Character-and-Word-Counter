/**
CO222 PROGRAMMING METHODOLOGY
PROJECT 2 : FREQUENCY OF WORD OR CHARACTER GENERATOR

E/17/356
H.P.S.UPEKHA


**/


//HEADERS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>



//STRUCTURE FOR CHARACTERS
typedef struct C{
char characterValue ;
int count;
struct C *next;
}Character;



//STRUCTURE  FOR WORDS
typedef struct W{
char word[100];
int wCount;
struct W *next;
}Words;

char mode='w';      			         //default mode  >>> to count the frequency of words
int n =10; 						        //No of rows of the graph   (default no.of iterations)
int wfound=0;   				        //to check whether -w flag is used
int cfound=0;   				        //to check whether -c flag is used

int wordNodes=0;                      // NUmber of words nodes
int characterNodes=0;  					//Number of character nodes 

char argument[100];                 // string to copy arguments in the program
char iterations[100];                 // argument after -l
int graphMode=0;              	  //default way to print the graph - non scaled
int maxWordLength=0;		  	  //to find the maximum length of the word
float Cpercentage=0.0;        	  //to find the character percentage

char FilesToOpen[100][500];  	//array to store the names of the files to be open
int FileNum=0;       			        //Number of files present (files which can open)



//Function to convert uppercase string into lowercase
char * Lower (char *s);

//Function to get  the number of digits before the point in the percentage value
int Digits(float percentage);


//main function
int main(int argc,char *argv[]){

/*WHEN 1 ARGUMENT*/
if (argc==1){
    printf("No input files were given\n");
    printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
    exit(1);
}

/*WHEN THERE ARE 2 ARGUMENTS*/

if (argc==2){
     if( ((strcmp("-c",argv[1]))==0 ) ||  ((strcmp("--scaled",argv[1]))==0 ) ||   (( strcmp("-w",argv[1]))==0  )){    //when -c , -w or --scaled flags are used
         printf("No input files were given\n");
        printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
        exit(1);
    }
   else if ((strcmp("-l",argv[1]))==0 ){            //When -l flag is used
        printf("Not enough options for [-l]\n");
        printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
        exit(1);
    }

    else  {
        strcpy(argument,argv[1]);             //for arguments starting with ' - ' character
        if (argument[0]=='-'){
            printf("Invalid option [%s]\n",argv[1]);
            printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
            exit(1);

        }
        else {
            FILE *fp;                           //File pointer
            fp=fopen(argv[1],"r");     // to open the file in read mode

            if (fp==NULL){               // if the file doesn't exit
            printf("Cannot open one or more given files\n");
            exit(1);
}
else{
    strcpy(FilesToOpen[0],argument);       //Add the file name into the list where the files are to be opened
    FileNum++;
}
        }

    }

    }


/*WHEN THERE ARE MORE THAN 3 AREGUMENTS*/

if(argc>=3){
    for (int m=1;m<argc;m++){
            if ((strcmp(argv[m],"-w"))==0 ) {          //when -w flag is used
                mode='w';
                wfound=1;
                break;
              }
        }

        for (int m=1;m<argc;m++){
            if ((strcmp(argv[m],"-c"))==0 ) {        //when -c flag is used
                mode='c';
                cfound=1;
                break;
              }
        }

if (wfound==1 && cfound==1){              //when both -c and -w are used in the arguments list
    printf("[-c] and [-w] cannot use together\n");
    printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
    exit(1);
   }


   //IF --scaled flag is used

   for (int m=1;m<argc;m++){
if ((strcmp(argv[m],"--scaled"))==0 ) {          // when --scaled flag is used
                graphMode=1;                                   //a scaled graph as the output
                break;

              }
   }


    for (int m=1;m<argc;m++){

             if ((strcmp(argv[m],"-l"))==0 ){          // when -l flag is used


                    if ((m)== argc-1){                      //if -l is used as the last argument
                    printf("Not enough options for [-l]\n");
                    printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                    exit(1);
                }


                if ((strcmp(argv[m+1],"0"))==0 ){       // if the argument after -l is zero (0)
                    exit(1);

                }

                else{
                int flag1=0,flag2=0;
                strcpy(iterations,argv[m+1]);            //copy the argument after -l into a string called iterations
                if (iterations[0]=='-' ){
                    for(int k=1;iterations[k]!='\0';k++){
                        if ((isdigit(iterations[k]))==0){       //check whether if there are non digits in the argument after -l
                            flag1=1;
                            break;


                        }
                    }
                    if (flag1==1){
                        printf("Invalid options for [-l]\n");         //if all are not digits  after - in the  argument after -l
                        printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                        exit(1);
                    }
                    else{
                        printf("Invalid option(negative) for [-l]\n");      // if all are digits after - in the argument  which means negative values
                        printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                        exit(1);
                    }

                }
                else{
                        for(int k=0;iterations[k]!='\0';k++){
                        if ((isdigit(iterations[k]))==0){        //check whether there are digits
                             flag2=1;
                            break;


                        }
                    }

                    if (flag2==1){
                        printf("Invalid options for [-l]\n");         //if all are not digits
                        printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                        exit(1);
                    }
                    else{
                        n=atoi(iterations);            //if all are digits convert that string into an integer
                        break;
                    }
                }



    }
         }


    }


   for (int m=1;m<argc;m++){

        strcpy(argument,argv[m]);
        if (((strcmp(argument,"-w"))!=0)   &&  ((strcmp(argument,"-c"))!=0)  &&  ((strcmp(argument,"-l"))!=0)   &&  ((strcmp(argument,"--scaled"))!=0) ){
            if (argument[0]=='-'){                                      //if  the 1st character of the argument starts with ' -' character
                printf("Invalid option [%s]\n",argument);
                printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                exit(1);
            }
            else{
                if ((strcmp(argv[m-1],"-l"))==0){          // if the previous argument is -l
                    continue;
                }


                else{
                    FILE *fp;    //File pointer
                    fp=fopen(argument,"r");          //open the file in the read mode

            if (fp==NULL){         //if the file doesn't exist
            printf("Cannot open one or more given files\n");
            //fclose(fp);
            exit(1);
            }

            else{
                strcpy(FilesToOpen[FileNum],argument);          //Copy the file name to array list ,where the files to be opened
                FileNum++;                                                              //increment the number of files
                fclose(fp);                                                                  //close the file

            }




                }
            }
        }

   }

}



/***TO FIND THE FREQUENCY OF A CHARACTER */

if (mode=='c'){

char ch;                                                    //to read the characters from the file
int TotalCount=0;                                    //total number of characters

Character *head, *newnode,*look;       // pointers
head=0;                                                    //initialize the head to NULL
for(int i=0;i<FileNum;i++){



FILE *fp=NULL;                                   //File pointer

fp=fopen(FilesToOpen[i],"r");             //open the file in the read mode




while (1){
    ch=fgetc(fp);                     //reading the characters
    if(ch==EOF){                    //at the end of the fie stop the process
        break;
    }
    if (isalnum(ch)){              // check whether the character  is an alphanumeric character
    TotalCount++;

    ch=tolower(ch);                //convert the character into lower case

     if (head==0){                                                                      //When adding the first record
    newnode=(Character*)malloc(sizeof (Character));            //creating the 1st node

   ( newnode->characterValue)=ch;                                          //adding the character
    newnode->count=1;                                                     //start counting the characters
    characterNodes=1;
	newnode->next=0;


     head=newnode;

    }

else{

//Check whether that character is already present in the linked list
look=head;
int flag=1;         //to check whether the character is present in the linked list
while(look!=0){
     // compare the character  and the characters already present  in the linked list
     if(look->characterValue==ch){
         look->count++;         //if that character  already present increment the relevant count accordingly
         flag=0;
        break;                      //Break the loop if the character  is found
    }

    look=look->next;
}
if (flag==1){                                                                       // if the character doesn't exist in the linked list
newnode=(Character*)malloc(sizeof (Character));     //create a new node
    look=head;
    while(look->next!=0){
        look=look->next;                                                    //new character is added at the end of the existing linked list
    }

    look->next=newnode;
    newnode->next=0;                            //Make that the last node in the list
    (newnode->characterValue)=ch;       //add the character into that
    newnode->count=1;                          //initialize the count from one
    characterNodes++;							//to count the number of character nodes in the linkd list


}
}
}
}

fclose(fp);                                             //close the file

}

//If no nodes are created it means that no data to process in the input files 

if (characterNodes==0){
	printf("No data to process\n");
	exit(1);
}

/*To sort the linked list*/

Character *x1,*x2;    //pointers
    char ctemp;         //temporary variable to store the character
    int itemp;             //temporary variable to store the count of the characters


    //sort the linked list according to the descending order of the counts of the characters
    for (x1=head;x1->next!=0;x1=x1->next){
        for(x2=head;x2->next!=0;x2=x2->next){
            if ((x2->count)<( x2->next->count)){

                ctemp=x2->characterValue;               //store the values into the temporary variables
                itemp=x2->count;

                x2->characterValue=(x2->next->characterValue);
                x2->count=x2->next->count;
                                                                                                        //swap the values
                x2->next->count=itemp;
                x2->next->characterValue=ctemp;
                }

            }
    }






//To print the graph

if (n>=characterNodes){                                //if the no of rows given by the user is grater than total number of nodes in the list 
    n=characterNodes;                                      //giving the output for no.of character nodes  (which is the maximum possible )
}
if (graphMode==0){                   //without scaling
look=head;
printf("\n");
for (int i=0;i<n;i++){
    Cpercentage=(look->count)/(TotalCount*1.0)*100.0;         //character percentage calculation
    /*
    printf("%-15s     %0.2f %%\n",look->word,wPercent);
*/


int  boxes=Cpercentage*(80-3-1-6)/100;          // size of one box in the graph

//printing the bar graph
		printf("   \u2502");
		for(int k=0;k<boxes;k++){
		printf("\u2591");
	}
	printf("\n");
	printf(" %c ",look->characterValue);      //displaying the character
	printf("\u2502");

	for(int k=0;k<boxes;k++){
			printf("\u2591");

	}
	printf("%.2f%%",Cpercentage);           //displaying the character percentage
	printf("\n");



	printf("   \u2502");
		for(int k=0;k<boxes;k++){
		printf("\u2591");
	}
	printf("\n");


	printf("   \u2502\n");
    look=look->next;                    //goes to the next node

    }

    printf("   \u2514");

for(int i=0;i<(80-1-3);i++){
	printf("\u2500");
}


printf("\n");

}

if (graphMode==1){           // when --scaled flag is used  (a scaled graph as the output)

    look=head;
    printf("\n");


    float HighestPercentage=look->count/(TotalCount*1.0)*100.0;      //percentage of the first row element
    int  Maxboxes=(80-1-(7+Digits(HighestPercentage)));        // ﬁrst row of the graph fully occupy the max print width.
    //Printing the first row
    printf("   \u2502");
		for(int k=0;k<Maxboxes;k++){
		printf("\u2591");
	}
	printf("\n");
	printf(" %c ",look->characterValue);         //character of the first row
	printf("\u2502");

	for(int k=0;k<Maxboxes;k++){
			printf("\u2591");

	}
	printf("%.2f%%",HighestPercentage);         // frequency of the first row character
	printf("\n");



	printf("   \u2502");
		for(int k=0;k<Maxboxes;k++){
		printf("\u2591");
	}
	printf("\n");


	printf("   \u2502\n");

	 look=look->next;                //goes to the next node



for (int i=1;i<n;i++){
    Cpercentage=(look->count)/(TotalCount*1.0)*100.0;           //percentages of character frequencies
    /*
    printf("%-15s     %0.2f %%\n",look->word,wPercent);
*/


int  boxes=Cpercentage*(Maxboxes/HighestPercentage);          // size of one box in the graph

//printing the other rows according to the above scale
		printf("   \u2502");
		for(int k=0;k<boxes;k++){
		printf("\u2591");
	}
	printf("\n");
	printf(" %c ",look->characterValue);                              //display the character
	printf("\u2502");

	for(int k=0;k<boxes;k++){
			printf("\u2591");

	}
	printf("%.2f%%",Cpercentage);                                   // displaying the character percentage
	printf("\n");



	printf("   \u2502");
		for(int k=0;k<boxes;k++){
		printf("\u2591");
	}
	printf("\n");


	printf("   \u2502\n");
    look=look->next;                                                //go to the next node

    }

    printf("   \u2514");

for(int i=0;i<(80-1-3);i++){
	printf("\u2500");
}


printf("\n");

}

exit(1);
}

/**TO FIND THE FREQUENCY OF WORD**/

if (mode=='w'){

char WORD[150];
char New[100];



int newLength,x,wTotal=0;

float wPercent=0.0;                     //word frequency percentage
Words  *head,*newnode,*look;  //pointers

head =0;                                       //initialize to NULL

for (int i=0;i<FileNum;i++){

FILE *fp=NULL;                                          //File pointer
fp=fopen(FilesToOpen[i],"r");                   //Open the file in the read mode



while (fscanf(fp,"%s",WORD)!=EOF){      //getting words till the end of the file


    Lower(WORD);                                       //To convert the word into lower case


 /* Pre-processing */
    int j=0;
for(int k=0;WORD[k]!='\0';k++){
    if (isalnum(WORD[k])){            //if the characters of the word are alphanumeric add them into the new string  called NEW
        New[j]=WORD[k];
        j++;
    }

}
New[j]='\0';                                     //null at the end of the string

newLength=strlen(New);
if(newLength!=0){                         //After preprocessing if the word length is not equal to zero, it is counted as a  word
    wTotal++;                                   //count the total number of words


if (head==0){                                                                        //When adding the first word
    newnode=(Words*)malloc(sizeof (Words));                  //creating the node

    strcpy(newnode->word,New);                                         //copy the word in to the list
    newnode->wCount=1;                                                       //initiate counting
    wordNodes=1;
    newnode->next=0;


     head=newnode;

    }

else{

//Check whether that character is already present in the linked list
look=head;
int flag=1;                                        // to check whether the character is present in the linked list
while(look!=0){
  x=strcmp(look->word,New);       // compare the word and the words in the linked list
     if(x==0){
         look->wCount++;                //if that word already present increment the relevant count accordingly
         flag=0;
        break;                                  //Break the loop if the word is found
    }

    look=look->next;
}
if (flag==1){                                                            // if the word doesn't exist in the linked list
newnode=(Words*)malloc(sizeof (Words));     //create a new node
    look=head;
    while(look->next!=0){
        look=look->next;                                          //new word is added at the end of the existing linked list
    }

    look->next=newnode;
    newnode->next=0;                                        //Make that the last node in the list
    strcpy(newnode->word,New);                      //copy the word into that
    newnode->wCount=1;                                  //initialize the count from one
    wordNodes++;
}

}

}
}

fclose(fp);                                                        //close the file
}

//No nodes created means no data to process in the files 

if (wordNodes==0){
	printf("No data to process\n");
	exit(1);
}

//Sorting the linked list

    Words *x1,*x2;
    char ctemp[100];                      //temporary variable to store the word
    int itemp;                                  //temporary variable to store the count of words

    for (x1=head;x1->next!=0;x1=x1->next){
        for(x2=head;x2->next!=0;x2=x2->next){
            if ((x2->wCount)<( x2->next->wCount)){

                strcpy(ctemp,x2->word);                                 //store the values in temporary variables
                itemp=x2->wCount;

                strcpy(x2->word,(x2->next->word));
                x2->wCount=x2->next->wCount;

                x2->next->wCount=itemp;                             //swap the values
                strcpy(x2->next->word,ctemp);
                }

            }
    }
    
  
  if (n>=wordNodes){                                //if the no of rows given by the user is grater than total number of nodes in the list 
    n=wordNodes;                                      //giving the output for no.of word nodes  (which is the maximum possible )
}


//To find the word with maximum length

look=head;
for (int i=0;i<n;i++){
    if ((strlen(look->word))>maxWordLength){
        maxWordLength=strlen((look->word));                        //to find the maximum length of the word
    }
    look=look->next;                                                                   //go to the next node
}



//To print the graph






if (graphMode==0){                                                                 //graph without scaling

look=head;
printf("\n");
for (int i=0;i<n;i++){
    wPercent=(look->wCount)/(wTotal*1.0)*100.0;                    //percentages of word count frequencies
    /*
    printf("%-15s     %0.2f %%\n",look->word,wPercent);
*/


int  boxes=wPercent*(80-maxWordLength-(7+Digits(wPercent)))/100;                 // size of one box in the graph

//printing the rows of the bar graph
		printf(" %-*s\u2502",(maxWordLength+1)," ");
		for(int k=0;k<boxes;k++){
		printf("\u2591");
	}
	printf("\n");
	printf(" %-*s",(maxWordLength+1),look->word);                 //display the word
	printf("\u2502");

	for(int k=0;k<boxes;k++){
			printf("\u2591");

	}
	printf("%.2f%%",wPercent);                                                 //display the percentage of word frequency
	printf("\n");



	printf(" %-*s\u2502",(maxWordLength+1)," ");
		for(int k=0;k<boxes;k++){
		printf("\u2591");
	}
	printf("\n");


	printf(" %-*s\u2502\n",(maxWordLength+1)," ");
    look=look->next;                                                                    //goto the next node

    }

    printf(" %-*s\u2514",(maxWordLength+1)," ");

for(int i=0;i<(80-maxWordLength-3);i++){
	printf("\u2500");
}


printf("\n");


}

if (graphMode==1){                                           //if --scaled flag is used
float HighestPercentage;


look=head;
printf("\n");


HighestPercentage=look->wCount/(wTotal*1.0)*100.0;        //percentage of the first row element

int  Maxboxes=(80-maxWordLength-(7+Digits(HighestPercentage)));                             // first row of the graph fully occupy the max print width.

//printing the first row
printf(" %-*s\u2502",(maxWordLength+1)," ");
		for(int k=0;k<Maxboxes;k++){
		printf("\u2591");
	}
	printf("\n");
	printf(" %-*s",(maxWordLength+1),look->word);               //display the first word
	printf("\u2502");

	for(int k=0;k<Maxboxes;k++){
			printf("\u2591");

	}

	printf("%.2f%%",HighestPercentage);                                 //display the first word frequency percentage
	printf("\n");



	printf(" %-*s\u2502",(maxWordLength+1)," ");
		for(int k=0;k<Maxboxes;k++){
		printf("\u2591");
	}
	printf("\n");


	printf(" %-*s\u2502\n",(maxWordLength+1)," ");



look=look->next;                                                                            //go to the next node



for (int i=1;i<n;i++){
    wPercent=(look->wCount)/(wTotal*1.0)*100.0;                     //percentages of word frequencies

    /*
    printf("%-15s     %0.2f %%\n",look->word,wPercent);
*/


int  boxes=wPercent*(Maxboxes/HighestPercentage);               // size of one box in the graph
//printing the other rows
		printf(" %-*s\u2502",(maxWordLength+1)," ");
		for(int k=0;k<boxes;k++){
		printf("\u2591");
	}
	printf("\n");
	printf(" %-*s",(maxWordLength+1),look->word);                    //display the word
	printf("\u2502");

	for(int k=0;k<boxes;k++){
			printf("\u2591");

	}
	printf("%.2f%%",wPercent);                                                      //display the percentages of frequencies
	printf("\n");



	printf(" %-*s\u2502",(maxWordLength+1)," ");
		for(int k=0;k<boxes;k++){
		printf("\u2591");
	}
	printf("\n");


	printf(" %-*s\u2502\n",(maxWordLength+1)," ");
    look=look->next;

    }

    printf(" %-*s\u2514",(maxWordLength+1)," ");

for(int i=0;i<(80-maxWordLength-3);i++){
	printf("\u2500");
}


printf("\n");


}



exit(1);
}



return 0;
}



/**Function to convert a string into a lower case */
char * Lower (char *s){
for (int i=0;s[i]!='\0';i++){
    if (s[i]>='A'  && s[i]<='Z'){       //if the character is in uppercase
        s[i]=s[i]+32;                          //convert the character to the lower case
    }
}

return s;

}

/**Function to get  the number of digits before the point in the percentage value */
int Digits(float percentage){
int temp,count=0;
temp=percentage;
while (temp!=0){
    count++;
    temp/=10;
}
return count;
}











