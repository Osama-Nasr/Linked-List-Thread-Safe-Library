# Linked List Safe (LLSafe) Library

The Linked List Safe (LLSafe) library provides a thread-safe implementation of a linked list data structure in C. It allows concurrent access to the linked list by multiple threads, ensuring data integrity and preventing race conditions.

## Usage

The LLSafe library consists of two main files: `LLSafe.h` and `LLSafe.c`. To use the library in your project, follow these steps:

1. Copy the `LLSafe.h` and `LLSafe.c` files into your project directory.
2. Include the `LLSafe.h` header file in your source code:

```c
#include "LLSafe.h"
```
## Running the Project

To run the project, follow the instructions provided below. The project involves creating and managing multiple threads that will concurrently access a global linked list, perform additions and deletions, and ensure thread safety using locking mechanisms.

### Linux Environment

1. Compile the LinkedList library by executing the following commands:
   ```bash
   gcc -c LinkedList.c -o LinkedList.o
   ar rcs libLinkedList.a LinkedList.o
   ```

2. Compile the main program by running the following command:
   ```bash
   gcc threadHandling.c -L. -lLinkedList -o threadHandling -lpthread
   ```

3. Run the compiled program using the command:
   ```bash
   ./threadHandling
   ```

### Compilation with Solution

If you want to compile the code with the solution, follow these steps:

1. Compile the main program with the LinkedList library and the pthread library:
   ```bash
   gcc -o solution solution.c LinkedList.c -lpthread
   ```

2. Execute the compiled program:
   ```bash
   ./solution
   ```

## Notes and Considerations

- The provided LinkedList library is designed to ensure thread safety for multi-threaded use. The user does not need to worry about thread synchronization as the library handles it internally.
- The library allows the user to create multiple lists, and the threads associated with different lists will not interfere with each other. Thread synchronization is only required for threads working on the same list.
- The steps provided assume a Linux environment. Please make sure to have the necessary dependencies installed on your system.
- The library has been compiled using the given commands, producing the `libLinkedList.a` file. These commands can be adjusted as per your specific setup or requirements.
- The program involves creating and managing threads, and it is expected to run with the desired synchronization and functionality.

Feel free to modify and experiment with the code as needed, and enjoy exploring the multi-threaded capabilities of the LinkedList library in a safe and synchronized manner!
### Book Structure

The library includes a `Book` structure that can be used as the data type for the elements stored in the linked list. Each book has an ID, author name, and content. The `Book` structure is defined as follows:

```c
typedef struct Book {
    int id;
    char* author;
    char* content;
} Book;
```

### Initializing a Linked List

To create and initialize a linked list, use the `init_list` function. It takes a pointer to a `LinkedList` structure and initializes it with the specified values:

```c
LinkedList list;
Node* head = NULL;
init_list(&list, head, 0);
```

The `LinkedList` structure contains a `head` pointer to the first node of the list and a `changeFirst` flag to indicate if the first node has changed.

### Adding Elements to the List

To add elements to the linked list, use the `append` function. It takes a pointer to the `LinkedList` and the data to be added as arguments:

```c
append(&list, data);
```

The `append` function adds the data to the appropriate position in the list based on the comparator function defined for the list.

### Removing Elements from the List

To remove an element from the linked list at a specific index, use the `deleteNodeByIndex` function. It takes a pointer to the `LinkedList` and the index of the node to be removed as arguments:

```c
deleteNodeByIndex(&list, index);
```

The `deleteNodeByIndex` function removes the node at the specified index from the list and frees the associated memory.

### Printing the List

To print the contents of the linked list, use the `printList` function. It takes a pointer to the `LinkedList` and a function pointer to a custom print function for the data type as arguments:

```c
printList(&list, printData);
```

The `printList` function iterates over the linked list and calls the specified print function for each node's data.

## Thread Safety

The LLSafe library ensures thread safety by using a mutex lock (`list_mutex`) to synchronize access to the linked list operations. This prevents multiple threads from accessing the list simultaneously and ensures data consistency.

## Example

Here's an example of using the LLSafe library to create a linked list of books:

```c
#include <stdio.h>
#include <stdlib.h>
#include "LLSafe.h"

int main() {
    LinkedList list;
    Node* head = NULL;
    init_list(&list, head, 0);

    // Create and append books to the list
    Book* book1 = createBook(1, "Author 1", "Content 1");
    Book* book2 = createBook(2, "Author 2", "Content 2");

    append(&list, book1);
    append(&list, book2);

    // Print the list
    printf("List of Books:\n");
    printList(&list, printBook);

    return

 0;
}
```

In this example, two books are created using the `createBook` function, and then appended to the linked list using the `append` function. The list is then printed using the `printList` function with the `printBook` print function.

## Limitations

- The LLSafe library is designed for single-process multi-threaded applications and does not support inter-process communication.
- The library does not handle memory deallocation when destroying the linked list. It's the responsibility of the user to free the memory of any dynamically allocated data.

## License

The LLSafe library is open source and released under the [MIT License](https://opensource.org/licenses/MIT). Feel free to use, modify, and distribute the library according to the terms of the license.
