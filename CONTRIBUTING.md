
# Contributing to ProjectName

This page describes how to write code that corresponds to the norms of this project.

## Code Style Guidelines

- **Function and File Naming**:
  - Use the `p_` prefix for the functions and files of the **parsing** part.
  - Use the `e_` prefix for the functions and files of the **execution** part.
  
- **Descriptive Function Names**:
  - Function names should be descriptive and use underscores (`_`) to separate words.
  
- **Function Comments**:
  - Every function must include a comment block above it that follows this format:

    ```c
    /**
     * @brief Adds two integers and returns the result.
     * 
     * @param a The first integer to be added.
     * @param b The second integer to be added.
     * This function takes two integers, adds them together, and returns the result.
     * It is designed to be used in simple arithmetic operations.
     * 
     * @return The sum of the two integers.
     */
    int add(int a, int b)
    {
        return a + b;
    }
    ```

    - These comments will be very helpful in understanding each other's code.

## Git Workflow

- **Branching**:
  - After cloning the git repository, create a new branch to work on:
    ```bash
    git checkout -b feature/new-feature
    ```

- **Merging and Testing**:
  - After implementing new features, merge your branch with the `main` branch and test thoroughly to ensure everything works fine.
  - Only push your changes to the remote repository once the testing is complete and everything is working properly.

- **Commit Messages**:
  - Use descriptive commit messages in the following format:
    ```bash
    git commit -m "Add feature X"
    git commit -m "Fix issue X"
    ```

