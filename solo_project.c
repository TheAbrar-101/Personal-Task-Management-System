#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define fixed_task 7
#define string 100
#define stack 50
#define queue 50
static void clear_screen(void)
{
    system("cls");
}
const char daily_task[fixed_task][string]= {"Wake up early","Exercise","Study","Check emails","Coding","Playing Football","Sleep early"};
struct node
{
    char task[string];
    struct node *next;
};
struct node *head=NULL;

char undo_stack[stack][string];
int top=-1;

char Queue_array[queue][string];
int Qfront=0,Qrear=0,Qcount=0;

void undo_push(char *x)
{
    if(top<stack-1)
        strcpy(undo_stack[++top],x);
}
char* undo_pop()
{
    if(top>=0)
        return undo_stack[top--];
    return NULL;
}

void enqueue(char* x)
{
    if(Qcount<queue)
    {
        strcpy(Queue_array[Qrear],x);
        Qrear=(Qrear+1)%queue;
        Qcount++;
    }
}
char* dequeue()
{
    static char temp[string];
    if (Qcount>0)
    {
        strcpy(temp,Queue_array[Qfront]);
        Qfront=(Qfront+1)%queue;
        Qcount--;
        return temp;
    }
    return NULL;
}

void add_task(char* x)
{
    struct node* newNode=(struct node*)malloc(sizeof(struct node));
    strcpy(newNode->task,x);
    newNode->next=NULL;
    if(!head)
        head=newNode;
    else
    {
        struct node* temp=head;
        while(temp->next)
            temp=temp->next;
        temp->next=newNode;
    }
}
void delete_task(char* x)
{
    struct node *temp =head,*previous =NULL;
    while(temp&&strcmp(temp->task, x)!=0)
    {
        previous=temp;
        temp=temp->next;
    }
    if (temp)
    {
        if(!previous)
            head=temp->next;
        else
            previous->next=temp->next;
        undo_push(temp->task);
        free(temp);
        printf("Task deleted and saved to undo...\n");
    }
    else
        printf("Task not found...\n");
}
void view_task()
{
    struct node* temp=head;
    int i=1;
    while(temp)
    {
        printf("%d. %s\n",i++,temp->task);
        temp=temp->next;
    }
    if(i==1)
        printf("No tasks available...\n");
}

int main()
{
    int c;
    char task[string];

    while(1)
    {
        clear_screen();
        printf("\n\t\t\t\t Personal Task Organizer \n\n");
        printf("\t1. View daily fixed tasks\n");
        printf("\t2. Add Task to To-Do List\n");
        printf("\t3. Delete task from To-Do list\n");
        printf("\t4. View To-Do List\n");
        printf("\t5. Undo last deletion\n");
        printf("\t6. Add upcoming task\n");
        printf("\t7. Process next upcoming task\n");
        printf("\t8. Exit\n\n");
        printf("\tChoose: ");
        scanf("%d",&c);
        getchar();

        switch(c)
        {
        case 1:
            for(int i=1;i<fixed_task;i++)
                printf("\t%d. %s\n",i,daily_task[i]);
            break;
        case 2:
            printf("Enter task: ");
            fgets(task,string,stdin);
            task[strcspn(task,"\n")]=0;
            add_task(task);
            break;
        case 3:
            printf("Enter task to delete: ");
            fgets(task,string,stdin);
            task[strcspn(task,"\n")]=0;
            delete_task(task);
            break;
        case 4:
            view_task();
            break;
        case 5:
        {
            char* restored=undo_pop();
            if(restored)
            {
                add_task(restored);
                printf("Restored: %s\n",restored);
            }
            else
                printf("Nothing to undo...\n");
            break;
        }
        case 6:
            printf("Enter upcoming task: ");
            fgets(task,string,stdin);
            task[strcspn(task,"\n")]=0;
            enqueue(task);
            break;
        case 7:
        {
            char* next_task=dequeue();
            if (next_task)
                printf("Processing: %s\n",next_task);
            else
                printf("No upcoming tasks...\n");
            break;
        }
        case 8:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice...\n");
        }
        printf("\nPress Enter to continue...");
        getchar();
    }
}
