# Invoice-Generation-System
A C++ Program which generates an invoice against a list of items.

The program has two components, thus having two classes
 One for the contents of the Item-List to be displayed on the invoice.
 The other one for storing the Invoice generated each time.
 
 We create an invoice by selecting the various items from the Items-List and mentioning it's quantity
 The invoice is finally generated in printed text format along with the total price.
 
 I have used an array of class objects
  One associated with the items namely items-id.
  Other being the invoice-id.
 Both the invoice and the various items have a unique id, that id being the index of the array of objects
 
 Indexing of objects in both cases start with 1.
