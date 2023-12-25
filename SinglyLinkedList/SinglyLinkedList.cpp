#include <iostream>
using namespace std;

class SinglyLinkedList
{
public:
	struct Node
	{
		int data = 0;
		Node* next = nullptr;
	};

private:
	Node* begin = nullptr;
	Node* end = nullptr;
	int count = 0;

	void Swap(Node* a, Node* b)
	{
		int temp = a->data;
		a->data = b->data;
		b->data = temp;
	}

	void SwapByIndex(int index1, int index2)
	{
		Node* node1 = GetNodeAt(index1);
		Node* node2 = GetNodeAt(index2);

		if (node1 != nullptr && node2 != nullptr)
		{
			Swap(node1, node2);
		}
	}

	Node* GetNodeAt(int index)
	{
		if (index < 0 || index >= count)
		{
			return nullptr;
		}

		Node* current = begin;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}

		return current;
	}

public:
	void AddToBegin(int data)
	{
		Node* newElem = new Node();
		newElem->data = data;
		newElem->next = begin;
		if (begin == nullptr)
		{
			end = newElem;
		}
		begin = newElem;
		count++;
	}

	void AddToEnd(int data)
	{
		Node* newElem = new Node();
		newElem->data = data;
		if (end == nullptr)
		{
			begin = newElem;
		}
		else
		{
			end->next = newElem;
		}
		end = newElem;
		count++;
	}

	void InsertInto(int data, int position)
	{
		if (position >= count)
		{
			AddToEnd(data);
			return;
		}
		else if (position <= 0)
		{
			AddToBegin(data);
			return;
		}

		Node* newElem = new Node();
		newElem->data = data;
		int i = 1;
		Node* beforeNew = begin;
		while (i++ != position)
		{
			beforeNew = beforeNew->next;
		}
		newElem->next = beforeNew->next;
		beforeNew->next = newElem;

		count++;
	}

	void DeleteFromBegin()
	{
		if (count == 0)
		{
			return;
		}
		Node* temp = begin;
		begin = begin->next;
		delete temp;
		count--;
		if (begin == nullptr)
		{
			end = nullptr;
		}
	}

	void DeleteFromEnd()
	{
		if (count == 0)
		{
			return;
		}
		DeleteByIndex(count - 1);
	}

	void DeleteByIndex(int position)
	{
		if (position <= 0)
		{
			DeleteFromBegin();
			return;
		}

		if (position >= count)
		{
			position = count - 1;
		}

		int i = 1;
		Node* beforeDel = begin;
		while (i++ != position)
		{
			beforeDel = beforeDel->next;
		}
		Node* sacrifice = beforeDel->next;
		beforeDel->next = sacrifice->next;
		delete sacrifice;
		count--;
		if (beforeDel->next == nullptr)
		{
			end = beforeDel;
		}
	}

	void Clear()
	{
		while (begin != nullptr)
		{
			DeleteFromBegin();
		}
	}

	void Print() const
	{
		if (count == 0)
		{
			cout << "Empty list!\n";
			return;
		}
		Node* current = begin;
		while (current != nullptr)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	int GetCount() const
	{
		return count;
	}

	int IndexOf(int data) const
	{
		if (count == 0)
		{
			return -1;
		}
		Node* temp = begin;
		int i = 0;
		while (i < count)
		{
			if (data == temp->data)
			{
				return i;
			}
			i++;
			temp = temp->next;
		}

		return -1;
	}

	bool IsEmpty() const
	{
		if (count == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int LastIndexOf(int data) const
	{
		if (count == 0)
		{
			return -1;
		}

		Node* current = begin;
		int lastFoundIndex = -1;
		int currentIndex = 0;

		while (current != nullptr)
		{
			if (current->data == data)
			{
				lastFoundIndex = currentIndex;
			}

			currentIndex++;
			current = current->next;
		}

		return lastFoundIndex;
	}

	void Reverse()
	{

		Node* prev = nullptr;
		Node* current = begin;
		Node* next = nullptr;

		end = begin;

		while (current != nullptr)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}

		begin = prev;
	}

	void SortAsc()
	{
		if (count <= 1)
		{
			return;
		}

		bool swapped;
		Node* current;
		Node* next = nullptr;

		do
		{
			swapped = false;
			current = begin;

			while (current->next != next)
			{
				if (current->data > current->next->data)
				{
					Swap(current, current->next);
					swapped = true;
				}
				current = current->next;
			}
			next = current;

		} while (swapped);
	}

	void Shuffle()
	{

		srand(static_cast<unsigned int>(time(nullptr)));

		for (int i = count - 1; i > 0; --i)
		{
			int j = rand() % (i + 1);
			SwapByIndex(i, j);
		}
	}

	int* ToArray() const
	{
		if (count == 0)
		{
			return nullptr;
		}

		int* array = new int[count];
		Node* current = begin;

		for (int i = 0; i < count; i++)
		{
			array[i] = current->data;
			current = current->next;
		}

		return array;
	}

	int operator[](int index) const
	{
		if (index < 0 || index >= count)
		{

			cout << "Error: Index out of bounds\n";

		}

		Node* current = begin;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}

		return current->data;
	}

	int& operator[](int index)
	{
		if (index < 0 || index >= count)
		{

			cout << "Error: Index out of bounds\n";
			return begin->data;
		}

		Node* current = begin;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}

		return current->data;
	}

	friend ostream& operator<<(ostream& os, const SinglyLinkedList& list)
	{
		if (list.count == 0)
		{
			os << "Empty list!";
			return os;
		}

		Node* current = list.begin;
		while (current != nullptr)
		{
			os << current->data << " ";
			current = current->next;
		}

		return os;
	}

};

ostream& operator<<(ostream& os, const SinglyLinkedList& list);

int main()
{
	SinglyLinkedList sll;

	sll.AddToEnd(10);
	sll.AddToEnd(20);
	sll.AddToEnd(30);
	sll.AddToEnd(40);
	sll.Print();

	sll.AddToBegin(50);
	sll.AddToBegin(60);
	sll.AddToBegin(70);
	sll.AddToBegin(80);
	sll.Print();

	cout << "count: " << sll.GetCount() << "\n";
	cout << "index of 70: " << sll.IndexOf(70) << ", index of 90: " << sll.IndexOf(90) << "\n";

	sll.InsertInto(-1, -1);
	sll.Print();
	sll.InsertInto(2, 2);
	sll.Print();
	sll.InsertInto(22, 22);
	sll.Print();

	sll.DeleteByIndex(0);
	sll.DeleteByIndex(1);
	sll.DeleteByIndex(2);
	sll.Print();

	cout << "Is the list empty?\n " << sll.IsEmpty() << "\n";

	int lastIndex = sll.LastIndexOf(30);
	cout << "Last index of 30: " << lastIndex << "\n";

	cout << "Original list: ";
	sll.Print();

	sll.Reverse();
	cout << "Reversed list: ";
	sll.Print();

	sll.SortAsc();
	cout << "Sorted list: ";
	sll.Print();

	sll.Shuffle();
	cout << "Shuffled list: ";
	sll.Print();

	int* array = sll.ToArray();
	cout << "List converted to array: ";
	for (int i = 0; i < sll.GetCount(); i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	delete[] array;

	cout << "Element at index 2: " << sll[2] << endl;

	sll[2] = 100;
	cout << "New list: ";
	sll.Print();

	cout << "List: " << sll << endl;


}
