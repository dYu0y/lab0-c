#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    queue_contex_t *queue = (queue_contex_t *) malloc(sizeof(queue_contex_t));
    if (!queue) {
        return NULL;
    }
    queue->size = 0;
    INIT_LIST_HEAD(&queue->chain);
    return &queue->chain;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    queue_contex_t *queue = container_of(l, queue_contex_t, chain);
    element_t *iter, *safe;
    list_for_each_entry_safe (iter, safe, &queue->chain, list) {
        q_release_element(iter);
    }
    free(queue);
}


/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    element_t *new = (element_t *) malloc(sizeof(element_t));
    if (!new) {
        return false;
    }

    new->value = strdup(s);
    if (!new->value) {
        free(new);
        return false;
    }

    list_add(&new->list, head);
    list_entry(head, queue_contex_t, chain)->size++;
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    element_t *new = (element_t *) malloc(sizeof(element_t));
    if (!new) {
        return false;
    }

    new->value = strdup(s);
    if (!new->value) {
        free(new);
        return false;
    }

    list_add_tail(&new->list, head);
    list_entry(head, queue_contex_t, chain)->size++;
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    list_entry(head, queue_contex_t, chain)->size--;
    struct list_head *node_removed = head->next;
    list_del(node_removed);
    element_t *entry_removed = list_entry(node_removed, element_t, list);
    if (sp) {
        strncpy(sp, entry_removed->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return entry_removed;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    list_entry(head, queue_contex_t, chain)->size--;
    struct list_head *node_removed = head->prev;
    list_del(node_removed);
    element_t *entry_removed = list_entry(node_removed, element_t, list);
    if (sp) {
        strncpy(sp, entry_removed->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return entry_removed;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    return list_entry(head, queue_contex_t, chain)->size;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || list_empty(head)) {
        return false;
    }
    struct list_head *f = head->next, *b = head->prev;
    while (f != b && f->next != b) {
        f = f->next;
        b = b->prev;
    }
    list_del(b);
    q_release_element(list_entry(b, element_t, list));
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (!head) {
        return false;
    }
    if (list_empty(head) || list_is_singular(head)) {
        return true;
    }

    bool current_dup = false;
    element_t *iter, *safe;
    LIST_HEAD(pending_list);
    list_for_each_entry_safe (iter, safe, head, list) {
        if (&safe->list != head && strcmp(iter->value, safe->value) == 0) {
            current_dup = true;
            list_move(&iter->list, &pending_list);
        } else if (current_dup) {
            current_dup = false;
            list_move(&iter->list, &pending_list);
        }
    }

    list_for_each_entry_safe (iter, safe, &pending_list, list) {
        q_release_element(iter);
    }

    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
