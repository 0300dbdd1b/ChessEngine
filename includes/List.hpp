#ifndef __LIST__
# define __LIST__
# include <iostream>
# include "./utils.hpp"

template <class T> class list_item;
template <class T> class List;

template <class T>
class list_item
{
	friend class List<T>;
	private:
		T data;
		list_item<T> *next;
		list_item(const T &value) {data=value, next=NULL;}
		list_item(const T &value, list_item<T> *item) {data=value, next=item;}
};

template <class T>
class List
{
	public:

		List();
		List(const List<T> &move_list);
		~List(){empty();};
		


		bool add_first(const T &data);
		bool add_last(const T &data);
		bool add_at(const T &data, size_t i );

		void remove_first(void);
		void remove_last(void);
		void remove_at(size_t i);
		void empty(void);

		const T get_first(const T &value);
		const T get_last(const T &value);
		const T at(size_t i);

		inline size_t size(void) const {return nb_items;}
		inline bool is_empty(void) const {return nb_items==0;}

		List<T> operator=(const List &list);
		List<T> operator+(const List &list);
		void print(void);
	private:
		list_item<T> *first_item;
		list_item<T> *last_item;
		size_t nb_items;


};

template <class T>
List<T>::List()
{
	first_item = last_item = NULL;
	nb_items = 0;
}

template <class T>
List<T>::List(const List<T> &move_list)
{	
	first_item = last_item = NULL;
	nb_items = 0;
	list_item<T> *items = move_list.first_item;
	while (items != NULL)
	{
		add_last(items->data);
		items = items->next;
	}
}

template <class T>
bool List<T>::add_first(const T &data)
{
	list_item<T> *new_item = new list_item<T>(data);
	if (new_item == NULL)
		return (false);
	new_item->next = first_item;
	first_item = new_item;
	if (nb_items == 0)
		last_item = new_item;
	++nb_items;
	return (true);
}

template <class T>
bool List<T>::add_last(const T &data)
{
	if (last_item == NULL)
		return (add_first(data));
	list_item<T> *new_item = new list_item<T>(data);
	if (new_item == NULL)
		return (false);
	last_item->next = new_item;
	last_item = new_item;
	if (nb_items == 0)
		first_item = new_item;
	++nb_items;
	return (true);
}

template <class T>
bool List<T>::add_at(const T &data, size_t i)
{
	if (i <= 0)
		return (add_first(data));
	else if (i >= nb_items)
		return (add_first(data));
	else
	{
		list_item<T> *new_item = new list_item<T>(data);
		list_item<T> *prev_item = first_item;
		if (new_item == NULL)
			return (false);
		for (size_t n = 0; n < i-1; ++n)
			prev_item = prev_item->next;
		new_item->next = prev_item->next;
		prev_item->next = new_item;
		++nb_items;
		return (true);
	}
}

template <class T>
void List<T>::remove_first(void)
{
	if (nb_items > 0)
	{
		list_item<T> *to_delete = first_item;
		first_item = first_item->next;
		delete to_delete;
		--nb_items;
		if (nb_items == 0)
			last_item = NULL;
	}
}

template <class T>
void List<T>::remove_last(void)
{
	if (nb_items > 0)
	{
		if (nb_items > 1)
		{
			delete first_item;
			last_item = first_item = NULL;
		}
		else
		{
			list_item<T> *second_to_last = first_item;
			for (size_t i = 0; i < nb_items - 1; ++i)
				second_to_last = second_to_last->next;
			delete second_to_last->next;
			second_to_last->next = NULL;
		}
		--nb_items;
	}
}

template <class T>
void List<T>::remove_at(size_t i)
{
	if (i > 0 && i < nb_items)
	{
		if (i == 0)
			return (remove_first());
		else
		{
			list_item<T> *prev = first_item;
			for (size_t n = 0; n < i - 1; ++n)
				prev = prev->next;
			list_item<T> *to_delete = prev->next;
			prev->next = to_delete->next;
			delete to_delete;
			--nb_items;
		}
	}
}

template <class T>
void List<T>::empty(void)
{
	while (nb_items > 0)
		remove_first();
}

template <class T>
const T List<T>::get_first(const T &value)
{
	if (nb_items == 0)
		return (0);
	value = first_item->data;
	return (value);

}

template <class T>
const T List<T>::get_last(const T &value)
{
	if (nb_items == 0)
		return (0);
	value = last_item->data;
	return (value);

}

template <class T>
const T List<T>::at(size_t i)
{
	T value;
	if (i < 0 || i >= nb_items)
		return (value);
	list_item<T> *target = first_item;
	for (size_t n = 0; n < i; ++n)
		target = target->next;
	value = target->data;
	return (value);	
	
}

template <class T>
List<T> List<T>::operator=(const List<T> &list)
{
	if (this != &list)
	{
		empty();
		list_item<T> *items = list.first_item;
		while (items != NULL)
		{
			add_last(items->data);
			items = items->next;
		}

	}
	return (*this);
}

template <class T>
List<T> List<T>::operator+(const List &list)
{
	list_item<T> *i = list.first_item;
	while (i != NULL)
	{
		add_last(i->data);
		i = i->next;
	}
	return (*this);
}

template <class T>
void  List<T>::print(void)
{
	list_item<T> *i = first_item;
	while (i != NULL)
	{
		std::cout << i->data << " ";
		i = i->next;
	}
	std::cout << std::endl;
}
#endif