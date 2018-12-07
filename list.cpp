#include <cstdlib>

/* Node class */
template <typename T>
class Node
{
  private:
    T value;
    Node<T> *next;
    Node<T> *prev;
  public:
    Node(T theVal)
    {
        this->value = theVal;
        this->next = NULL;
        this->prev = NULL;
    }
    T GetValue()
    {
        return value;
    }
    Node<T>* GetNext()
    {
        return next;
    }
    Node<T>* GetPrev()
    {
        return prev;
    }
    void SetValue(T theVal)
    {
    	this->value = theVal;
    }
    void SetNext(Node<T>* n)
    {
        this->next = n;
    }
    void SetPrev(Node<T>* p)
    {
        this->prev = p;
    }
};

/* List class */
template <typename T>
class List
{
    Node<T> *head;
    Node<T> *tail;
public:
    // Constructor
    List();
    // Copy Constructor
    List(List<T>& otherList);
    // Destructor
    ~List();
    // Insertion Functions
    void InsertAtHead(T item);
    void InsertAtTail(T item);
    void InsertAfter(T toInsert, T afterWhat);
    // Lookup Functions
    Node<T> *GetHead();
    Node<T> *GetTail();
    Node<T> *SearchFor(T item);
    // Deletion Functions
    void DeleteElement(T item);
    void DeleteHead();
    void DeleteTail();
    // Utility Functions
    int Length();
};

template <typename T>
List<T>::List()
{
  head = NULL;
  tail = NULL;
}

template <typename T>
List<T>::List(List<T>& otherList)
{
  Node<T> *p = otherList.head;
  Node<T> *n = NULL;
  while(p!=NULL){
    Node<T> *o = new Node<T>(p->GetValue());
    if(n!=NULL){
      n->SetNext(o);
      o->SetPrev(n);
    }else{
      head = o;
    }
    p = p->GetNext();
    n = o;
    tail = o;
  }
}

template <typename T>
List<T>::~List()
{
  Node<T> *temp;
  while (head != NULL)
  {
    temp = head;
    head = head->GetNext();
    delete temp;
  }
  tail = NULL;
}

template <typename T>
void List<T>::InsertAtHead(T item)
{
  Node<T> *temp = new Node<T>(item);
  if(head==NULL){
    temp->SetNext(NULL);
    temp->SetPrev(NULL);
    head = temp;
    tail = head;
  }else{
    temp->SetNext(head);
    head->SetPrev(temp);
    head = temp;
  }
}

template <typename T>
Node<T>* List<T>::GetHead()
{
  return head;
}

template <typename T>
Node<T>* List<T>::GetTail()
{
  return tail;
}

template <typename T>
void List<T>::InsertAtTail(T item)
{
  Node<T> *temp = new Node<T>(item);
  if(head==NULL){
    temp->SetNext(NULL);
    temp->SetPrev(NULL);
    head = temp;
    tail = head;
  }else{
    tail->SetNext(temp);
    temp->SetPrev(tail);
    temp->SetNext(NULL);
    tail = temp;
  }
}

template <typename T>
void List<T>::InsertAfter(T toInsert, T afterWhat)
{
  Node<T> *temp = new Node<T>(toInsert);
  Node<T> *curr = SearchFor(afterWhat);
  if(curr!=NULL){
    Node<T> *next = curr->GetNext();
    curr->SetNext(temp);
    temp->SetPrev(curr);
    if(next!=NULL){
      temp->SetNext(next);
      next->SetPrev(temp);
    }else{
      temp->SetNext(NULL);
    }
  }else{
    tail->SetNext(temp);
    temp->SetPrev(tail);
    temp->SetNext(NULL);
    tail = temp;
  }
}

template <typename T>
Node<T> *List<T>::SearchFor(T item)
{
  Node<T> *first = head;
  while(first!=NULL){
    if(first->GetValue()==item){
      return first;
    }
    first = first->GetNext();
  }
  return NULL;
}

template <typename T>
void List<T>::DeleteElement(T item)
{
  Node<T> *curr = SearchFor(item);
  Node<T> *temp;
  if(curr!=NULL){
    if(curr==head)
      temp = head->GetNext();
      temp->SetPrev(NULL);
      head = temp;
    }else if(curr==tail){
      temp = tail->GetPrev();
      temp->SetNext(NULL);
      tail = temp;
    }else{
      Node<T> *previous = curr->GetPrev();
      Node<T> *next = curr->GetNext();
      previous->SetNext(next);
      next->SetPrev(previous);
  }
}

template <typename T>
void List<T>::DeleteHead()
{
  if(head!=NULL){
    Node<T> *temp = head->GetNext();
    if(temp!=NULL){
      temp->SetPrev(NULL);
      head = temp;
    }else{
      head = NULL;
      tail = NULL;
    }
  }
}

template <typename T>
void List<T>::DeleteTail()
{
  if(tail!=NULL){
    Node<T> *temp = tail->GetPrev();
    if(temp!=NULL){
      temp->SetNext(NULL);
      tail = temp;
    }else{
      head = NULL;
      tail = NULL;
    }
  }
}

template <typename T>
int List<T>::Length()
{
  int count = 0;
  Node<T> *first = head;
  while(first!=NULL){
    first = first->GetNext();
    count++;
  }
  return count;
}
