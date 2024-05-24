# Assembly-Line-Management-System
This project was developed to apply and enhance my C++ Object Oriented Programming skills. By simulating an assembly line with multiple workstations, I aimed to create a practical application that demonstrates the concepts of class design, object management, and system integration. The project also provides an opportunity to solve a complex problem by breaking it down into manageable modules and milestones.

#Features
The main features of this project include:

Utilities Module: Handles parsing input files to set up and configure the assembly line.
* setFieldWidth, getFieldWidth, extractToken: Manage token extraction and field width.
* setDelimiter, getDelimiter: Manage delimiters for token separation.

Station Module: Manages individual stations on the assembly line.
* getItemName, getNextSerialNumber, getQuantity, updateQuantity, display: Manage station details and display.

CustomerOrder Module: Processes customer orders as they move through the assembly line.
* isOrderFilled, isItemFilled, fillItem, display: Manage and display order details.

Workstation Module: Extends the Station class to manage order processing at each station.
* fill, attemptToMoveOrder, setNextStation, getNextStation, display: Manage workstation operations and display.

LineManager Module: Manages the overall assembly line process.
* reorderStations, run, display: Manage and display the status of the assembly line.
