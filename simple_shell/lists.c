#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to the new node
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head = malloc(sizeof(list_t));
	if (!new_head)
		return NULL;

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	new_head->str = _strdup(str);
	if (str && !new_head->str)
	{
		free(new_head);
		return NULL;
	}

	new_head->next = *head;
	*head = new_head;
	return new_head;
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to the new node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));
	if (!new_node)
		return NULL;

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	new_node->str = _strdup(str);
	if (str && !new_node->str)
	{
		free(new_node);
		return NULL;
	}

	if (*head)
	{
		list_t *node = *head;
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;

	return new_node;
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return i;
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	if (!head || !*head)
		return 0;

	if (index == 0)
	{
		list_t *node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return 1;
	}

	list_t *prev_node = *head;
	list_t *node = prev_node->next;
	unsigned int i = 1;

	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return 1;
		}
		i++;
		prev_node = node;
		node = node->next;
	}

	return 0;
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node = *head_ptr;

	while (node)
	{
		list_t *next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}
