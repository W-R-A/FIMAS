# Thread Safe Data Sharing #

To facilitate thread-safe data sharing, a data manager class was written to simplify to the process. The class ensures data integrity by using an internal mutex, with all data access through the public API. 

The class follows the concept of "getter" and "setter" methods which is a very efficient way of managing access to a shared resource. Using this paragrin, a method to store data can simply "set and forget" the data, with the class automatically aquiring, and critically, releasing the internal mutex, ensuring data integrity. This also abstrcts away the complexity of the mutexes, allowing effort to be spent improving the user interface rather than figuring out why there is a deadlock in the system. 