#include<stdio.h>
char memory[25000];

struct block{                               //Initialize block
    int datasize;
    int free;
    struct block *next;
    
};
struct block *head;
void *ptr=(void*)memory;                    //Create pointer variable and it points to the address of memory[0]
void *preptr;
void *endptr=&memory[25000];
int totalsize=0;

void MyFree(void *ad){
    struct block *freetemp=head ;           //create struct block and  its points to the head block
    if(ad==&memory){                        //check given  address is first node of the linkedlist
            freetemp->free=0;

            head=NULL;

    }
    else{
        while((freetemp)!=ad){
            freetemp=freetemp->next;        //after finding relevant block make free=0

        }
        freetemp->free=0;
        totalsize=totalsize-freetemp->datasize;

    }
    if(freetemp->next->free==0){                                                  //check front neighbor block is free if it is then merge
        freetemp->datasize=freetemp->datasize + freetemp->next->datasize + sizeof(struct block);
        freetemp->next=freetemp->next->next;
    }

}


void *MyMalloc(int size){
        totalsize=totalsize+size+sizeof(struct block);
        if( totalsize<25000){             //check memory range

            struct block *slot;
            if(head==NULL){
                slot=ptr;
                head=ptr ;
                ptr=ptr+size+sizeof(struct block);

                slot->next=ptr;
                slot->datasize=size;
                slot->free=1;


                return slot;

            }
            else {
                struct  block *pretemp,*prev, *temp=head ;
                while(temp!=ptr  ){                 //check there is free space available in an allocated memory slots
                     if(temp->datasize>(size+sizeof(struct block))){
                        if(temp->free==0)
                            break;
                    }

                    prev=temp;
                    temp=temp->next;
                }


                if( temp!=ptr    ){   //check are those free spaces in the middle of the memeory
                    preptr=temp;
                    preptr=preptr+size+sizeof(struct block);
                    slot=preptr;
                    slot->next=temp->next;
                    temp->next=slot;
                    slot->datasize= temp->datasize -size;
                    temp->datasize=size;
                    temp->free=1;
                    slot->free=0;
                    return temp;

                    }
                else if(temp==ptr ) {    //if there are no free spaces in the middle of the memory
                    printf("yes\n");
                    slot=ptr;
                    prev->next=slot;
                    ptr=ptr+size+sizeof(struct block);
                    slot->next=ptr;
                    slot->free=1;
                    slot->datasize=size;

                    return slot;

                }
//
            }

         }
         else{                                                  //if given memory space grater than having memory space
                printf("Out of memory\n");

         }
}
