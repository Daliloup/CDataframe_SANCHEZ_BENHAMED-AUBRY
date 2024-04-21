# CDataframe_SANCHEZ_BENHAMED-AUBRY

**Link to the Github repository** : https://discord.com/channels/@me/1231540852443320422/1231696986533662812

This project is carried by Dali Sanchez and Yannis Benhamed--Aubry


The objective of this project is to create a Dataframe in C language.
The Dataframe is represented by columns containing elements.  
An element of the structure *COLUMN* represents one column.  
An element of the structure *DATAFRAME* represents one dataframe.

Several choices were needed to be made, here they are :
- A single column must contain the same type of elements, but different columns can contain different types.
- The data structure used for the Dataframe is a double linked list, each element of the list containing a column.

The double linked lists are made with the structure *lnode_*

The idea is first to make the basic functionalities, for simple manipulations of the dataframe : adding an element to a column, etc...
but also to add more advanced tools, such as sorting functions, etc..
