# Crescendo10k
The software associated with the CPSS FAR 10K rocket competition project titled "Crescendo"

This project uses PlatformIO

# Design rules:
- #Comments
-   Write understandable comments. they don't need to be pretty. Write the comments you would want to read if you had never seen your code before.  
-   Comments are strongly reccomended for these areas:
  -   Beggining of file (explain what the file is for)
  -   Beggining of function (explain what the function takes in, does, and then returns)
  -   FAQ. Places that were hard for you to understand (if you had to go to StackOverflow to get it, then so will the next person. save them the trouble if you can)
  -   Math. Mathematical equations in code are impossible to understand, comment what it is and what its doing
  -   Library Calls. Explain what the library function is doing if its not clear. No one wants dig through docs.

# Working as a Team:
## helpful terms for those new to git:
- git: 
  Git is the protocol and the set of tools used for version control and code colaboration
- repository: 
  a codebase. Can keep track of multiple versions.
- remote repository: 
  version of your project that is hosted on the Internet or network somewhere (GitHub in our case).
- local repository: 
  version of your project that is on your machine. You edit this and push changes into the remote repository
- branch: 
  an independent line of development. Branches serve as an abstraction for the edit/stage/commit process. You can think of them as a way to request a brand new working directory, staging area, and project history. We use them to work on a feature independantly from what others are working on.
- fetch: 
  updates your machine's image of the remote repository and lets you see the remote code without affecting your local repository. you can merge this fetched repository into your local one later.
- merge: 
  merging the code from one branch to another. We use this to add a complete feature into the working or "production" branch. we also use this to merge 'fetched' code from remote into your local repository so you can work on top of it while creating a new feature.
- pull: 
  Basically fetches and then merges into your local repository in one command. This can be more dangerous than fetching first as it immediately introduces changes to your local repository.

## Workflow Basics:

- Fetch and merge changes from the remote
- Create a branch to work on a new project feature
- Develop the feature on a branch and commit the work
- Fetch and merge from the remote again (in case new commits were made, make sure your feature still works with the current production)
- Push branch up to the remote



