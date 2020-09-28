#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max 10

struct node{
    char *name;
    struct node *dir[max];
    char *file[max];
    int dc,fc;
}*root,*ptr;

struct node* newNode(char *c){
    struct node* node = (struct node*)malloc(sizeof(struct node)); 
    node->name = c;
    node->dc=0;
    node->fc=0;
    for(int i=0;i<max;i++)
    {
        node->dir[i] = NULL; 
        node->file[i] = NULL;
    } 
    return(node);
}

void menu(){
    int choice;
    printf("\n-----------------------------------\nCurrent directory : %s\nEnter choice\n\t1.Create Directory\n\t2.Create file\n\t3.List\n\t4.Enter directory\n\t5.Delete file\n\t6.Delete directory\n\t7.Exit to root\n\t8.Search this directory\n\t9.Print details\n\t0.Exit\n\t\t:\t",ptr->name);
    scanf("%d",&choice);
    switch(choice){
        case 1:{
            char *s=(char *)malloc(sizeof(char));
            printf("\nEnter name : ");
            scanf("%s",s);
            ptr->dir[ptr->dc]=newNode(s);
            ptr->dc=ptr->dc+1;
            break;
        }
        case 2:{
            char *s=(char *)malloc(sizeof(char));
            printf("\nEnter name : ");
            scanf("%s",s);
            ptr->file[ptr->fc]=s;
            ptr->fc=ptr->fc+1;
            //printf("%d\n",ptr->fc);
            break;
        }
        case 3:{
            printf("\n directories : \n");
            for(int i=0;i<ptr->dc;i++){
                printf("\t%d. %s\n",i,ptr->dir[i]->name);
            }
            printf("\n files : \n");
            for(int i=0;i<ptr->fc;i++){
                printf("\t%d. %s\n",i,ptr->file[i]);
            }
            break;
        }
        case 4:{
            if(ptr->dc==0){
                printf("\nno directories\n");
                break;
            }
            int a;
            printf("Select\t:\n");
            for(int i=0;i<ptr->dc;i++){
                printf("\t%d. %s\n",i,ptr->dir[i]->name);
            }
            scanf("%d",&a);
            if(a<0 || a>=ptr->dc){
                printf("\nInvalid choice\n");
                break;
            }
            ptr=ptr->dir[a];
            printf("\nsuccessfully moved to %s",ptr->name);
            break;
        }
        case 5:{
            if(ptr->fc==0){
                printf("\nno files\n");
                break;
            }
            int a;
            printf("Select\t:\n");
            for(int i=0;i<ptr->fc;i++){
                printf("\t%d. %s\n",i,ptr->file[i]);
            }
            scanf("%d",&a);
            if(a<0 || a>=ptr->fc){
                printf("\nInvalid choice\n");
                break;
            }
            for(int i=a;i<ptr->fc-1;i++){
                ptr->file[i]=ptr->file[i+1];
            }
            ptr->fc=ptr->fc-1;
            printf("\nsuccessfully deled \n");
            break;
        }
        case 6:{
            if(ptr->dc==0){
                printf("\nNo directories\n");
                break;
            }
            int a;
            printf("Select\t:\n");
            for(int i=0;i<ptr->dc;i++){
                printf("\t%d. %s\n",i,ptr->dir[i]->name);
            }
            scanf("%d",&a);
            if(a<0 || a>=ptr->dc){
                printf("\nInvalid choice\n");
                break;
            }
            if(ptr->dir[a]->fc == 0 && ptr->dir[a]->dc == 0){
                printf("\nsuccessfully deleted %s",ptr->dir[a]->name);
                for(int i=a;i<ptr->dc-1;i++){
                    ptr->dir[i]=ptr->dir[i+1];
                }
                ptr->dc=ptr->dc-1;
                break;
            }
            printf("\n Cannot delete non empty directory!!!\n");
            break;
        }
        case 7:{
            printf("\nDone\n");
            ptr=root;
            break;
        }
        case 8:{
            char *x=(char *)malloc(sizeof(char));
            printf("\nEnter keyword\t:\t");
            scanf("%s",x);
            printf("\nMatching directroies : ");
            for(int i=0;i<ptr->dc;i++){
                if(strstr(ptr->dir[i]->name,x)){
                    printf("\n\t%d. %s",i,ptr->dir[i]->name);
                }
            }
            printf("\nMatching files : ");
            for(int i=0;i<ptr->fc;i++){
                if(strstr(ptr->file[i],x)){
                    printf("\n\t%d. %s",i,ptr->file[i]);
                }
            }
            break;
        }
        case 9:{
            printf("\n\tName of directory : %s\n\tNo.of directories : %d\n\tNo.of files : %d\n\tTotal members : %d\n",ptr->name,ptr->dc,ptr->fc,ptr->dc+ptr->fc);
            break;
        }
        case 0: exit(0);
        default : printf("\n Invalid\n");
        
    }
}

void initialize(){
    root=newNode("root");
    ptr=root;
   // printf("%s",root->name);
}

int main(){
    initialize();
    while(1)
        menu();
}