#ifndef __LIST_H
#define __LIST_H

struct list_head {
	struct list_head *prev, *next;
};

static inline void list_init(struct list_head *head)
{
	head->prev = head->next = head;
}

static inline void __list_add(struct list_head *list,
			struct list_head *prev, struct list_head *next)
{
	list->prev = prev;
	list->next = next;
	next->prev = list;
	prev->next = list;
}

static inline void list_add(struct list_head *list, struct list_head *head)
{
	__list_add(list, head, head->next);
}

static inline void list_add_tail(struct list_head *list, struct list_head *head)
{
	__list_add(list, head->prev, head);
}

#define LIST_HEAD(name)\
	struct list_head name = { &name, &name };

#define list_empty(head) ((head) == (head)->next)

#define list_entry(ptr, type, member)\
	((type *)((char *)(ptr) - (int)&((type *)0)->member))
#define list_first_entry(head, type, member)\
	list_entry((head)->next, type, member)

#define list_for_each_entry(entry, head, member)\
	for (entry = list_first_entry(head, typeof(*entry), member);\
		&entry->member != (head);\
		entry = list_first_entry(&entry->member, typeof(*entry), member))

#endif	/* list.h */