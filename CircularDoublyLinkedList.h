#pragma once
// This is the Circular Doubly Linked List.h header file of the TopSpin program. 
//
//CircularDoublyLinkedList.h
//
// This program was made by Andrew Simon.
// This program was made on 13/11/2016.
// This program was last modified on 24/11/2016.
//
// Parts of this code are based on the lecture slides regarding Circular Doubly Linked List.


template <class T>
class CDLinkedList {

	private:
		
		class Node {	
		public:
			Node(T val, Node * nx = nullptr, Node * pv = nullptr) : value(val), next(nx), previous(pv) {}
			T value;
			Node * next;
			Node * previous;
		};

	public:
		CDLinkedList();		// Will construct an empty CD linked list.
		~CDLinkedList();	// Will distroy an empty linked list.
		unsigned int size() const;	// Will return the number of items that are in the presently in the list.
		bool isEmpty() const;	// If the LL is empty it will return true, and false for vice versa.
		
		//NEW Shift function.
		void shift(int dir);

		void addHead(T value);	// Will add an T to the FRONT of the list.

		//Not needed. NVM actually needed.
		T removeHead();		// Will remove the front node and return the data value fount in it.
								// The only PRECONDITION being: the list must not already be empty.

		T retrieveHead() const;		//Will return the data value infront of the node.
										//PRECONDITION: List must not already be empty.

		void addTail(T value); // Will ADD a Piece to the end of the list.

		//Not needed. NVM actually needed.
		T removeTail();		// Will remove the last Node, and return the data value found in it.
								// Precondition: list must not be empty already.

		T retrieveTail() const;		// Return data value in last node.
										// Precondition: List must not be empty.

		void add(unsigned int n, T value);	// Add a new node contaning "piece" in position n on the list.
												// Precondition: n must be a valid position.

		T replace(unsigned int n, T value);	// Will replace the data value in psition n on the list with "piece" and return the replaced piece.
													// Precondition: n must be a valid list position.

		T remove(unsigned int n);	// Will remove the node at position n from the list and return the data value it contained.
										// Precondition: n must be a valid list position.

		T retrieve(unsigned int n) const;	// Will return the data reference from the node in position n.
												// Precondition: n must be a valid list position.

		CDLinkedList(const CDLinkedList<T> &other);	//Will act as the copy constructor.


	//Don't want external access to these important values.
	private:

		Node *m_head;
		Node *m_tail;
		unsigned int m_size =0;

};

//Default Initializations for CDLL
//Should be Good.
template <class T>
CDLinkedList<T> :: CDLinkedList() : m_head(NULL), m_tail(NULL), m_size(0) {

	//Initializes items to 0 and Null.

}

//Default Destructor for CDLL
//Should be Good - Check?
template <class T>
CDLinkedList<T> :: ~CDLinkedList() {

	Node *here = m_head;

	for (unsigned int i = 0; i < m_size; ++i)
	{
		Node *next = here->next;
		delete here;
		here = next;
	}
}

//Should be Good.
template <class T>
unsigned int CDLinkedList<T> :: size() const {

	//Returns the size of the CDLL.
	return m_size;

}

//Should be Good. - Check?
template <class T>
bool CDLinkedList<T> :: isEmpty() const {

	//Runs a quick t/f check to see if the size is 0.
	//If the size is 0, then is empty is true, else false.
	return(m_size == 0);

}

//Should be Good.
template <class T>
void CDLinkedList<T> :: addHead(T value) {
	
	//I think this is good.
	//Changes the direction of the pointers' chain head definition.
	Node *here = new Node(value, m_head, m_tail);
	if (m_size == 0) {
		m_head = here;
		m_tail = here;
	}
	m_head->previous = here;
	m_tail->next = here;

	//Incriment size of the CDLL by one.
	m_size++;

	//Is this needed? YES YES IT IS
	//m_head = here;
}

//Should be Good.
template <class T>
T CDLinkedList<T> :: retrieveHead() const {

	//Precondition: List is not already Empty.
	//Gets the head node.
	return m_head->value;

}

//Should be Good.
template <class T>
void CDLinkedList<T> :: addTail(T value) {

	//I think this is good.
	//Changes the direction of the pointers' chain tail definition.
	Node *here = new Node(value, m_head, m_tail);
	if (m_size == 0) {
		m_head = here;
		m_tail = here;
	}
	m_head->previous = here;
	m_tail->next = here;

	//Still increases the size by one.
	m_size++;

	//Is this needed?
	m_tail = here;

}

//Should be good.
template <class T>
T CDLinkedList<T> :: retrieveTail() const {

	//Precondition: List is not already empty.
	//Retrieves the tail node.
	return m_tail->value;

}

template <class T>
//Should be Good.
//Position, then value @ inserted position.
void CDLinkedList<T> :: add(unsigned int n, T value) {

	//Adds a node to the CDLL 
	//Precondition: n should be a valid position 1 <= n <= size()+1
	if (n == 1) {
		addHead(value);
	} else if (n == size() + 1) {
		addTail(value);
	} else {
		Node *here = m_head;
		//Does a boundry check.
		for (unsigned int k = 1; k < n - 1; k++) {
			here = here->next;
		}
		here->next = new Node(value, here->next);
		//Increments the size of the CDLL.
		m_size++;
	}


}

//Should be Good.
template <class T>
T CDLinkedList<T> :: replace(unsigned int n, T value) {

	//Replaces one node with another.
	//Precondition: n must be a valid current list position 1 <= n <=size().
	T returnValue;
	Node * here = m_head;
	//Does a boundry check.
	for (unsigned int k = 1; k < n; k++) { 
		here = here->next;
	}
	returnValue = here->value;
	here->value = value;

	return returnValue;

}

//Should be Good.
template <class T>
T CDLinkedList<T> :: remove(unsigned int n) {

	//Removes 
	// Precondition: n must be a valid current list position 1 <= n <= size().
	if (n == 1) {
		return removeHead();
	}

	if (n == size()) {
		return removeTail();
	}

	Node * here = m_head;
	for (unsigned int k = 1; k < n - 1; k++) {
		here = here->next;
	}
	Node * kill = here->next;
	T returnVal = kill->value;
	here->next = kill->next;
	delete kill;
	m_size--;
	return returnVal;


}

//Should be Good
template <class T>
T CDLinkedList<T> :: retrieve(unsigned int n) const {

	// precondition: n must be a valid current list position 1<=n<=size()
	if (n == 1) {
		return retrieveHead();
	}

	if (n == size()) {
		return retrieveTail();
	}

	Node * here = m_head;
	for (unsigned int k = 1; k < n; k++) {
		here = here->next;
	}
	return here->value;

}

//Should be Good
template <class T>
void CDLinkedList<T> :: shift(int dir) {

	//Needs to be fixed. It wants a return type?

	//1 for right.
	if (dir == 1) {

		m_head = m_head->previous;
		m_tail = m_tail->previous;
		return;


	//0 for left
	} else if (dir == 0) {

		m_head = m_head->next;
		m_tail = m_tail->next;
		return;

	}

}

//Should be Good: Is needed now.
template <class T>
T CDLinkedList<T> :: removeHead() {

	//Precondition: list is not already Empty.
	if (m_size == 0) {
		return NULL;
	} 

	Node * oldNode = m_head;
	T returnVal = m_head->value;
	m_head = m_head->next;
	m_tail->next = m_head;
	if (m_head == nullptr) m_tail = nullptr;
	m_size--;
	delete oldNode;
	return returnVal;

}

//Should be Good: Is needed now.
template <class T>
T CDLinkedList<T> :: removeTail() {

	//Precondition: list is not already empty.
	if (m_size == 0) {
		return NULL;
	}

	if (m_head == m_tail) {
		return removeHead();
	}

	Node * preTail = m_tail->previous;
	T returnVal = m_tail->value;

	preTail->next = m_head;
	delete m_tail;
	m_tail = preTail;
	m_size--;
	return returnVal;

}


//Copy constructor
template <class T>
CDLinkedList<T> :: CDLinkedList(const CDLinkedList<T> &other) {

	if (other.m_size == 0) {

		m_head = nullptr;
		m_tail = nullptr;
		m_size = 0;

	} else {

		m_size = other.m_size;
		m_head = new Node(other.m_head->value, nullptr, nullptr);
		if (other.m_tail == nullptr) {

			m_tail = m_head;

		} else {

			Node * copyFrom = other.m_head->next;
			Node *nextNode = m_head;

			while (copyFrom != m_head) {
				nextNode->next = new Node(copyFrom->value);
				copyFrom = copyFrom->next;
				nextNode = nextNode->next;

			}
			m_tail = nextNode;
		}

	}
}
