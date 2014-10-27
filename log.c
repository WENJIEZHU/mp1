/** @file log.c */
#include <stdlib.h>
#include <string.h>
#include "log.h"


void log_init(log_t *l) {
	l -> head = NULL;
	//l -> head -> prev = NULL;
	//l -> head -> next = NULL;
	l -> tail = NULL;
	//l -> tail -> prev = NULL;
	//l -> tail -> next = NULL;

}

void log_destroy(log_t* l) {
	node* nn = l ->head;

 	while(nn != NULL){
        	node* mm = nn -> next;
        	free(nn -> value);
		free(nn);
		nn = mm;
    	}
    	//free(l);
}


void log_push(log_t* l, const char *item) {
	//l -> head -> prev = NULL;
	//l -> tail -> next = NULL;	
	node * s = (node *) malloc(sizeof(node));
	//puts(sizeof(node));
    	s -> value = strdup(item);
	//s -> prev = NULL; s -> next = NULL;
	if (l -> head == NULL){
		l -> head = s;
		l -> tail = s;
		l -> tail -> next = NULL;
	}
	else{
		s -> next = l -> head;
		l -> head -> prev = s;
		l -> head = s;
		l -> head -> prev = NULL;
	}	
	//l ->tail = l ->head;

	//while(l -> tail-> next != NULL) {
	//	l -> tail = l -> tail->next;
	//}
	//l -> tail -> next = NULL;
	//free(s);
}


 
char *log_search(log_t* l, const char *prefix) {
   node* sting = l->head;
    //printf("head value %s\n", sting->value);
    while(sting != NULL){
       // sting = l -> head -> value;
        int r = strncmp((sting->value), prefix, strlen(prefix));
        //printf(" value %d\n", r);
        if (r == 0)
            return (sting->value);
        sting = sting -> next;
    }
    return NULL;
}
