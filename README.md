Inverted Search Using Hash Table (C)

##  Project Overview

This project implements an **Inverted Index** using the C programming language.  
It indexes words from multiple text files and enables efficient searching of words along with the files in which they appear and their frequency count.

##  Features

- Create database from multiple input text files
- Display indexed database contents
- Search for a word across files
- Save database to a backup file
- Update database from backup
- Prevent duplicate file indexing
- Efficient lookup using hashing


## Data Structures Used

- **Hash Table (28 Buckets)**
  - `a–z` → 0–25
  - digits → 26
  - special characters → 27

- **Main Node**
  - Stores word
  - File count
  - Pointer to sub-node list
  - Pointer to next main node

- **Sub Node**
  - Stores file name
  - Word occurrence count
  - Pointer to next sub node

- **Singly Linked List**
  - Maintains list of input files


## How It Works

1. Words from input files are read one by one.
2. A hash index is calculated using the first character.
3. If the word already exists:
   - Check if file already exists
   - Increment word count if present
   - Otherwise create a new sub-node
4. If word does not exist:
   - Create new main node
   - Attach sub-node with file details
5. Database can be saved and later reconstructed using update functionality.


## 🛠 Build Instructions (Using Makefile)

This project uses a **Makefile** for compilation.

To compile the project:

```bash
make
