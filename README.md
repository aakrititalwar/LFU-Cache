# LFU-Cache
Efficient Implementation of Least Frequently Used Cache with O(1) runtime complexity for all operations

Problem to be Solved :

Key Points and Thinking Process:

As given both put and get operations add to the usecount of the key value pair
we need to remove the key with the lowest usecount(frequency) , so we need  frequencies in sorted order.
Also, for keys with same frequency we need to remove the Least recently used
So for a group of keys with same frequency, the least Recently used should be accessible.
The moost important point in the problem is that for each key after any operation the frequency of the key changes only by 1

Approach:

First Approach:
My first approach was to use doubly linked list and hashmap with the follwing structure :

1. HashMap of (Key, pointer to ListNode) : unordered_map<int,ListNode*>
2. Doubly Linked List Node containing pair  of (freq, val)

1. for get operation - if key not in map return -1, if present return value from node
2. for put operation - if key present, change value and if not present add a node with freq 1 and value.

After both get and put operations the nodes for the keys move to the end of the next frequency.

Problem with Approach : if we have a large number keys for the same frequency we need to traverse all those keys to add the particular key node at the end of next frequency.

Efficient Algorithm:

we group together all the keys that have the same frequency and store it in a Least Recently Used fashion.
Use of nested Linked List where each node of the first linked list has another linkedlist and count of frequency and the nested linked list contains the key value pair.
We also have a hashmap of (Key, Pair(Pointer to FreqNode , pointer to Key-value Node)) 
Both are doubly linked list and each node of the frequency linkedlist contains head and tail pointers for the key value linked list. 

Code Overview :
1. Class KeyNode: Node contains properties Key and value. The KeyNode Linkedlist is specific to each node of freq linked list.

1. Class ListNode: Node contains freq(usecount), head and tail pointers for KeyNode list. 
   Functions:
   a) Get - returns val for the key and removes the node from the KeyNode  lisnked list of curr frequency
   b) 

1. Class LFUCache - initializes :
         a)empty linked list of type ListNode
         b)maxsize of cache
         c) unordered_map of type <int, pair<ListNode*,KeyNode*>>
         
   Functions:
   
 

