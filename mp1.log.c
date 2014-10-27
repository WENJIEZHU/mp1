/** @file log.c */
#include <stdlib.h>
#include <string.h>
#include "log.h"

/**
 * Initializes the log.
 *
 * You may assuem that:
 * - This function will only be called once per instance of log_t.
 * - This function will be the first function called per instance of log_t.
 * - All pointers will be valid, non-NULL pointer.
 *
 * @returns
 *   The initialized log structure.
 */
void log_init(log_t *l) {
	l -> head = NULL;
	//l -> head -> prev = NULL;
	//l -> head -> next = NULL;
	l -> tail = NULL;
	//l -> tail -> prev = NULL;
	//l -> tail -> next = NULL;

}
/**
 * Frees all internal memory associated with the log.
 * You may assume that:
 * - This function will be called once per instance of log_t.
 * - This funciton will be the last function called per instance of log_t.
 * - All pointers will be valid, non-NULL pointer.
 *
 * @param l
 *    Pointer to the log data structure to be destoryed.
 */
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

/**
 * Push an item to the log stack.
 *
 *
 * You may assume that:
* - All pointers will be valid, non-NULL pointer.
*
 * @param l
 *    Pointer to the log data structure.
 * @param item
 *    Pointer to a string to be added to the log.
 */
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

/**
 * Preforms a newest-to-oldest search of log entries for an entry matching a
 * given prefix.
 *
 * This search starts with the most recent entry in the log and
 * compares each entry to determine if the query is a prefix of the log entry.
 * Upon reaching a match, a pointer to that element is returned.  If no match
 * is found, a NULL pointer is returned.
 *
 *
 * You may assume that:
 * - All pointers will be valid, non-NULL pointer.
 *
 * @param l
 *    Pointer to the log data structure.
 * @param prefix
 *    The prefix to test each entry in the log for a match.
 *
 * @returns
 *    The newest entry in the log whose string matches the specified prefix.
 *    If no strings has the specified prefix, NULL is returned.
 */
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
