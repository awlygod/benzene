# Benzene: A Custom Database Engine in C++

## About the Project
Benzene is a lightweight and efficient custom database engine developed in C++. It supports essential CRUD operations (Create, Read, Update, Delete) and is designed to optimize data management through advanced indexing, caching, and disk management techniques.

### Key Features:
- **B-tree Indexing**: Implements B-trees for fast data retrieval and optimized search functionality.
- **LRU Cache System**: Reduces data access latency by keeping frequently used data in memory.
- **Pager Module**: Manages disk I/O operations efficiently, ensuring smooth data persistence.
- **SQL Query Processing**: A lexer and parser convert SQL queries into executable operations.
- **Modular Architecture**: Organized into distinct components for better maintainability and scalability.

## Implementation Details
Benzene's architecture is structured into six core components, each handling a crucial part of the database system:

### 1. `pager.hpp` - Disk I/O Manager
- Handles raw data pages, reading/writing to disk.
- Manages data movement between memory and storage.
- Acts as a "disk driver" for the database.

### 2. `btree.hpp` - B-Tree Data Structure
- Organizes and indexes data efficiently.
- Supports insertion, deletion, and search operations.
- Enhances query performance through structured indexing.

### 3. `lru_cache.hpp` - Least Recently Used Cache
- Improves performance by keeping frequently accessed pages in memory.
- Reduces disk I/O operations by managing a memory buffer.
- Determines which pages to retain in memory vs. write to disk.

### 4. `frontend.hpp` - Lexer & Parser
- Converts SQL queries into a format the database understands.
- **Lexer**: Breaks SQL strings into tokens (similar to words in a sentence).
- **Parser**: Interprets the tokens and forms a meaningful structure.
- Functions as the "translator" of the database.

### 5. `execution_engine.hpp` - Query Execution
- Processes parsed queries and executes them.
- Coordinates with `btree.hpp` and `pager.hpp` for data operations.
- Handles actual data manipulation (e.g., SELECT, INSERT, DELETE).
- Acts as the "worker" executing user commands.

### 6. `engine.hpp` - Core Coordinator
- Manages the lifecycle of database operations.
- Provides the public API for interacting with the database.
- Orchestrates all components to ensure smooth execution.
- Serves as the "brain" of the entire database system.

## Why Benzene?
Benzene is built for those who want:
- **A lightweight yet efficient custom database engine.**
- **A deep dive into database internals**, from indexing to query execution.
- **Optimized data retrieval and storage management.**
- **A modular and scalable architecture** for further enhancements.


Benzene is an ongoing project . 🚀 Feel free to explore, contribute, and improve the database engine.

