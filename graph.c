#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

struct listNode{
    char *dest;
    struct listNode* next;
};
struct Graph{
    int vert;
    struct AdjacencyList* listsArr;
    int* visit; // 1 is visited, 0 is not
};
struct AdjacencyList{
    struct listNode *head; //head node ptr
};
struct listNode* newlistNode(char *dest){
    struct listNode* newNode = (struct listNode*)malloc(sizeof(struct listNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
};

struct Graph* createGraph(int vert){ //makes an array of lists
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vert = vert;
    graph->listsArr = (struct AdjacencyList*)malloc(vert*sizeof(struct AdjacencyList));
    graph->visit = malloc(vert * sizeof(int));
    //head is null for each list, create empty graph
    for (int i = 0; i < vert; ++i){
        //each head of lists array is null, visit list is 0
        graph->listsArr[i].head = NULL;
        graph->visit[i] = 0;
    }
    return graph;
}
// adds the head vertex
void addHead(struct Graph* graph, char* vertex, int j){
    char *vertex2 = malloc(80*sizeof(char));
    strcpy(vertex2, vertex);
    struct listNode* newNode = newlistNode(vertex2);
    struct listNode* temp = graph->listsArr[j].head;
    if(temp == NULL){
        graph->listsArr[j].head = newNode;
        return;
    }
}

// adds edges after the head
void addEdge(struct Graph* graph, char *src, char *dest){   
    char *src2 = malloc(80*sizeof(char));
    strcpy(src2, src);
    char *dest2 = malloc(80*sizeof(char));
    strcpy(dest2, dest);

    // finds the correct head node to place edge, for source to destination
    int i;
    for(i = 0; i < graph->vert; i++){
        if(strcmp(graph->listsArr[i].head->dest, src2)==0){
            break;
        }
    }
    struct listNode* newNode = newlistNode(dest2);
    struct listNode* temp = graph->listsArr[i].head -> next;
    if(temp == NULL||strcmp(dest2, temp->dest)<0){ //places at queueHead of list, behind head
        newNode->next = graph->listsArr[i].head->next;
        graph->listsArr[i].head->next = newNode;
    }
    else{ //places in between or at end of list
        while(temp->next!=NULL){
            if(strcmp(dest2,temp->dest)>0 && strcmp(temp->next->dest,dest2) >0){
                newNode -> next = temp -> next;
                temp -> next = newNode -> next;
                temp -> next = newNode;
                break;
            }
            temp=temp->next;
        }
        temp->next=newNode;
    }
    // finds the opposite head node to place the edge, destination to source
    int j;
    for(j = 0; j < graph->vert; j++){
        if(strcmp(graph->listsArr[j].head->dest, dest2)==0){
            break;
        }
    }
    newNode = newlistNode(src2);
    temp = graph->listsArr[j].head -> next;

    if(temp == NULL||strcmp(src2, temp->dest)<0){
        newNode->next = graph->listsArr[j].head->next;
        graph->listsArr[j].head->next = newNode;
        return;
    }else{
        while(temp->next!=NULL){
            if(strcmp(src2,temp->dest)>0 && strcmp(temp->next->dest,src2) >0){
                newNode -> next = temp -> next;
                temp -> next = newNode -> next;
                temp -> next = newNode;
                return;
            }
            temp=temp->next;
        }
        temp->next=newNode;
    }
}

struct Queue{
    char *elements[SIZE];
    int queueHead;
    int queueTail;
};

struct Queue* createQueue() {
  struct Queue* queue = malloc(sizeof(struct Queue));
  queue->queueHead = -1;
  queue->queueTail = -1;
  return queue;
}

int queueEmpty(struct Queue* queue) {
    if (queue->queueTail == -1){
        return 1;
    }
    return 0;
}

void enqueue(struct Queue* queue, char* element){
    // allocate memory for new queue element
    char *element2 = malloc(80 * sizeof(char));
    strcpy(element2, element);
    if(queue->queueHead == -1){
        queue -> queueHead = 0;
    }
    queue -> queueTail++;
    queue -> elements[queue->queueTail] = element2;
}

int dequeue(struct Queue* queue, struct Graph* graph){
    char* element;
    int a;
    if (!queueEmpty(queue)) {
        element = queue -> elements[queue -> queueHead];
        for(int i = 0; i < graph -> vert; i++){ 
            if(strcmp(graph->listsArr[i].head->dest, element)==0){
                a = i;
                break;
            }
        }
        queue->queueHead++;
        if (queue->queueHead > queue->queueTail) {
            queue->queueHead = queue->queueTail = -1;
        }
        free(element);
    }
    return a;
}

void breadthFirstSearch(struct Graph* graph, char* first){
    char* first2 = first;
    struct Queue* queue = createQueue();

    // loops through adj array to find specified head vertex
    int i;
    for(i = 0; i < graph -> vert; i++){ 
        if(strcmp(graph->listsArr[i].head->dest, first2)==0){
            enqueue(queue, first2);
            graph->visit[i] = 1; // marks visited
            break;
        }
    }
    while (!queueEmpty(queue)) {
        int curr = dequeue(queue, graph); // dequeues visited vertex
        printf("%s ", graph->listsArr[curr].head->dest); // prints each visited value in order
        struct listNode* temp = graph->listsArr[curr].head;
        while(temp != NULL){ // loops through adjacency list
            char* adj = temp->dest;
            int j; 
            //finds correct vertex
            for(j = 0; j < graph -> vert; j++){ 
                if(strcmp(graph->listsArr[j].head->dest, adj)==0){
                    break;
                }
            }
            //if not yet visited, enqueue and mark as visited
            if(graph->visit[j] == 0){
                graph->visit[j] = 1;
                enqueue(queue, adj);
            }
            temp = temp -> next;
        }
    }
    // clears visit list to perform BFS again for next vertex
    for (int i = 0; i < graph->vert; ++i){
        graph->visit[i] = 0;
    }
    printf("\n");
    free(queue);
    return;
}

void freeMemory(struct Graph *graph){
    struct listNode* temp;
    struct listNode* p;
    for(int i = 0; i < graph->vert; i++){
        temp = graph->listsArr[i].head;
        p = graph->listsArr[i].head;
        while(p){
            temp = p;
            p = p->next;
            free(temp->dest);
            free(temp);
        }
    }
    free(graph->listsArr);
    free(graph->visit);
    free(graph); 
}

int main(int argc, char* argv[argc+1]){
    if(argc < 3){
        printf("error");
        return EXIT_SUCCESS;
    }
    //open file, scan
    FILE* fp = fopen(argv[1], "r");
    int line;

    //GRAPH FILE LOOP
    fscanf(fp, "%d\n", &line);
    char str[80];
    char vertex[80];
    char first[80];
    char second[80];
    struct Graph* graph = createGraph(line);

    for(int j = 0; j < line; j++){
        fscanf(fp, "%s\n", vertex);
        //if single string without space
        if(!strchr(vertex, ' ')){
            addHead(graph, vertex, j);
        }
    }
    while(fgets(str, line, fp) != NULL){
        sscanf(str, "%s %s\n", first, second);
        //if two strings with a space, separate
        if(strchr(str, ' ')){
            addEdge(graph,first,second);
        }
    }

    FILE* fp2 = fopen(argv[2], "r");
    while(fscanf(fp2, "%s\n", first)!=EOF){
        breadthFirstSearch(graph, first);
    }
    freeMemory(graph);
    fclose(fp);
    fclose(fp2);
}