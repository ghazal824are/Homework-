#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 100 // الحد الأقصى لحجم السلسلة النصية

typedef struct {
    char **buffer; 
    int head; 
    int tail; 
    int count; 
    int size; 
} CircularBuffer;

void initBuffer(CircularBuffer *cb, int bufferSize) {
    cb->buffer = (char **)malloc(bufferSize * sizeof(char *));
    for (int i = 0; i < bufferSize; i++) {
        cb->buffer[i] = (char *)malloc(MAX_STRING_SIZE * sizeof(char));
    }
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
    cb->size = bufferSize;
}

int enqueue(CircularBuffer *cb, const char *data) {
    if (cb->count == cb->size) {
        printf("المخزن ممتلئ (Overflow)\n");
        return -1; 
    }
    strcpy(cb->buffer[cb->tail], data);
    cb->tail = (cb->tail + 1) % cb->size;
    cb->count++;
    return 0;
}

int dequeue(CircularBuffer *cb, char *data) {
    if (cb->count == 0) {
        printf("المخزن فارغ (Underflow)\n");
        return -1; 
    }
    strcpy(data, cb->buffer[cb->head]);
    cb->head = (cb->head + 1) % cb->size;
    cb->count--;
    return 0; 
}

void printBuffer(CircularBuffer *cb) {
    if (cb->count == 0) {
        printf("المخزن فارغ.\n");
        return;
    }
    
    printf("محتويات المخزن:\n");
    for (int i = 0; i < cb->count; i++) {
        int index = (cb->head + i) % cb->size;
        printf("%s\n", cb->buffer[index]);
    }
}

void freeBuffer(CircularBuffer *cb) {
    for (int i = 0; i < cb->size; i++) {
        free(cb->buffer[i]);
    }
    free(cb->buffer);
}

int main() {
    CircularBuffer cb;

    int bufferSize;
    printf("أدخل حجم المخزن (يجب أن يكون أقل من 100): ");
    scanf("%d", &bufferSize);
    
  
    while (bufferSize <= 0 || bufferSize > MAX_STRING_SIZE) {
        printf("حجم غير صالح. أدخل حجمًا بين 1 و %d: ", MAX_STRING_SIZE);
        scanf("%d", &bufferSize);
    }

    initBuffer(&cb, bufferSize);

    char name[MAX_STRING_SIZE];
    printf("أدخل اسمك: ");
    getchar(); // للتخلص من newline المتبقي بعد scanf
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; 


    strcat(name, " CE-ESY");

    
    enqueue(&cb, name);


    char output[MAX_STRING_SIZE];
    if (dequeue(&cb, output) == 0) {
        printf("الناتج: %s\n", output);
    }

    if (cb.count == 0) {
        printf("المخزن فارغ الآن.\n");
    } else {
        
        printBuffer(&cb);
    }

    freeBuffer(&cb);

    return 0;
}
