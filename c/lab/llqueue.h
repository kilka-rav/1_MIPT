typedef struct _List {
        void* elt;
        struct _List* next;
} List;

int enqueue(List** queue, void*** elt) {
                List* new = malloc(sizeof(List));
                if ( ! new ) return -1;
                *elt = &new->elt;
                if ( ! *queue ) {
                        new->next = new;
                } else {
                        new->next = (*queue)->next;
                        (*queue)->next = new;
                }
                *queue = new;
        return 0;
}

int dequeue(List** queue, void** elt) {
        List* old;
                if (! *queue ) return -1;
                old = (*queue)->next;
                (*queue)->next = old->next;
                *elt = old->elt;
                if ( old == *queue) *queue = NULL;
                free(old);
        return 0;
}
