#include <stdio.h>
#include <stdlib.h>


struct mynode
{
    int value;
    struct mynode* next;
};

void push(struct mynode* queue, int value);
void pop(struct mynode* queue);
int empty(struct mynode* queue);

int main()
{
    struct mynode queue;
    queue.value = -1;
    queue.next = NULL;
    int value;
    scanf("%d",&value);
    push(&queue,value);


    while(empty(&queue)==0)
    {
        scanf("%d", &value);
        if(value==0)
        {
            printf("%d\n", queue.value);
            pop(&queue);
        }
        else
        {
            push(&queue,value);
        }
    }
}

void push(struct mynode* queue, int value)
{
    if(queue->value == -1) //if end
    {
        queue->value = value; //change the -1 to new value
        queue->next = (struct mynode*)malloc(sizeof(struct mynode)); //attach the new end
        if (queue->next == NULL) {
            printf("Memory not allocated.\n");
            exit(0);
        }
        queue->next->value = -1;
        queue->next->next = NULL; //set the new end
    }
    else
    {
        push(queue->next, value); //recusive: pass the next pointer
    }
}

void pop (struct mynode* queue)
{
    if (queue->next->value == -1) {
        queue->value = -1;
        free(queue->next);
        queue->next = NULL;
    }
    else {
        queue->value = queue->next->value;
        pop(queue->next);
    }
}

int empty(struct mynode* queue)
{
    if(queue->value==-1){
        return 1;
    }else{
        return 0;
    }
}
