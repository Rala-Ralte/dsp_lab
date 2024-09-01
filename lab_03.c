#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the node structure for the queue
typedef struct Node {
    char question[256];
    char answer[256];
    struct Node* next;
} Node;

// Define the queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create a new node
Node* createNode(char* question, char* answer) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->question, question);
    strcpy(newNode->answer, answer);
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to add an element to the queue
void enqueue(Queue* queue, char* question, char* answer) {
    Node* newNode = createNode(question, answer);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to remove an element from the queue
Node* dequeue(Queue* queue) {
    if (queue->front == NULL)
        return NULL;

    Node* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL)
        queue->rear = NULL;

    return temp;
}

// Function to write the queue contents to a file
void writeToFile(Queue* queue, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    Node* temp;
    while ((temp = dequeue(queue)) != NULL) {
        fprintf(file, "Question: %s\n", temp->question);
        fprintf(file, "Answer: %s\n", temp->answer);
        free(temp);
    }
    
    fclose(file);
}

int main() {
    Queue* queue = createQueue();
    char question[256];
    char answer[256];
    char choice;

    do {
        printf("Enter a question: ");
        fgets(question, sizeof(question), stdin);
        question[strcspn(question, "\n")] = '\0';  // Remove newline character

        printf("Enter the answer: ");
        fgets(answer, sizeof(answer), stdin);
        answer[strcspn(answer, "\n")] = '\0';  // Remove newline character

        enqueue(queue, question, answer);

        printf("Do you want to enter another question? (y/n): ");
        choice = getchar();
        getchar();  // To consume the newline character left by getchar
    } while (choice == 'y' || choice == 'Y');

    writeToFile(queue, "QandA.txt");

    printf("Questions and answers have been written to QandA.txt\n");

    // Free the queue structure
    free(queue);

    return 0;
}

