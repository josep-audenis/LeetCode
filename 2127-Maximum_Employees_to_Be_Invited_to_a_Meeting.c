// A company is organizing a meeting and has a list of n employees, waiting to be invited. They have arranged for a large circular table, capable of seating any number of employees.
// The employees are numbered from 0 to n - 1. Each employee has a favorite person and they will attend the meeting only if they can sit next to their favorite person at the table. The favorite person of an employee is not themself.
// 
// Given a 0-indexed integer array favorite, where favorite[i] denotes the favorite person of the ith employee, return the maximum number of employees that can be invited to the meeting.
// 
// - Example 1:
// Input: favorite = [2,2,1,2]
// Output: 3
// Explanation:
// The above figure shows how the company can invite employees 0, 1, and 2, and seat them at the round table.
// All employees cannot be invited because employee 2 cannot sit beside employees 0, 1, and 3, simultaneously.
// Note that the company can also invite employees 1, 2, and 3, and give them their desired seats.
// The maximum number of employees that can be invited to the meeting is 3. 
// 
// - Example 2:
// Input: favorite = [1,2,0]
// Output: 3
// Explanation: 
// Each employee is the favorite person of at least one other employee, and the only way the company can invite them is if they invite every employee.
// The seating arrangement will be the same as that in the figure given in example 1:
// · Employee 0 will sit between employees 2 and 1.
// · Employee 1 will sit between employees 0 and 2.
// · Employee 2 will sit between employees 1 and 0.
// The maximum number of employees that can be invited to the meeting is 3.
// 
// - Example 3:
// Input: favorite = [3,0,1,4,1]
// Output: 4
// Explanation:
// The above figure shows how the company will invite employees 0, 1, 3, and 4, and seat them at the round table.
// Employee 2 cannot be invited because the two spots next to their favorite employee 1 are taken.
// So the company leaves them out of the meeting.
// The maximum number of employees that can be invited to the meeting is 4.
//  
// Constraints:
// · n == favorite.length
// · 2 <= n <= 105
// · 0 <= favorite[i] <= n - 1
// · favorite[i] != i

struct Node {                                                                               //linked list node
    int value;
    struct Node* next;
};

struct Node* createNode(int value) {                                                        //constructor for linked list node
    struct Node* ret = malloc(sizeof(struct Node));
    ret->value = value;
    ret->next = NULL;

    return ret;
}

void addNode(struct Node** map, int index, int value) {                                     //adds a node to a list in a given position
    struct Node* tmp = map[index]->next;                                                    //store the current next node to mantain the linked list
    map[index]->next = createNode(value);                                                   //create the new node in the desired position
    map[index]->next->next = tmp;                                                           //link the previous next node to be the new node next node
}

int bfs(struct Node** map, int start, int n, int skip) {
    bool visited[n];
    int queue[n][2];
    memset(visited, 0, sizeof(visited));

    int front = 0, rear = 0, maxDist = 0;
    
    visited[start] = visited[skip] = true;
    queue[rear][0] = start;                                                                 //add the start node to the queue
    queue[rear++][1] = 0;                                                                   //set the distance to 0 and move the rear pointer

    while(front < rear) {                                                                   //execute while the queue is not empty
        int current = queue[front][0];                                                      //dequeu the front node
        int distCurrent = queue[front][1];                                                  //get dequeued node distance
        front++;
        
        for(struct Node* tmp = map[current]->next; tmp; tmp = tmp->next) {                  //check adjacent nodes
            int value = tmp->value;
            if(!visited[value]) {                                   
                visited[value] = true;
                int newDist = distCurrent + 1;                                              //increment distance
                queue[rear][0] = value;                                                     //enqueu the neighbour
                queue[rear++][1] = newDist;
                maxDist = (maxDist > newDist ? maxDist : newDist);                          //get the absolute max distance
            }
        }
    }
    
    return maxDist;
}

int maximumInvitations(int* favourite, int favouriteSize) {
    bool* visited = calloc(favouriteSize, sizeof(bool));
    struct Node** map = malloc(favouriteSize * sizeof(struct Node*));

    for(int i = 0; i < favouriteSize; i++) {
        map[i] = createNode(i);                                                             //create a node for every employee
    }
    for(int i = 0; i < favouriteSize; i++) {
        addNode(map, favourite[i], i);                                                      //add direction from favourite[i] -> i
    }
    
    int maxCycle = 0;
    int dCycle = 0;
    
    for(int i = 0; i < favouriteSize; i++) {
        if(!visited[i]) {
            int tmpVisited[favouriteSize];
            memset(tmpVisited, 0, sizeof(tmpVisited));
            
            int current = i;
            int dist = 0;
            
            while(!visited[current]) {
                
                visited[current] = true;
                tmpVisited[current] = ++dist;                                               //mark current distance
                int next = favourite[current];                                              //store the next person in chain
                
                if(tmpVisited[next] && tmpVisited[next] < tmpVisited[current]) {            //if we encounter a node that's already visited and it forms a cycle
                    
                    int cycleLength = dist - tmpVisited[next] + 1;                          //calculate cycle length
                    maxCycle = (maxCycle > cycleLength? maxCycle : cycleLength);            //get max cycle length
                    
                    if(cycleLength == 2) dCycle += 2 + bfs(map, current, favouriteSize, next) + bfs(map, next, favouriteSize, current); //if the cycle length is 2 calculate the additional distances using bfs
                
                    break;
                }       
                current = next;
            }
        }
    }
    
    return (maxCycle > dCycle ? maxCycle : dCycle);                                         //return the maximum of the longest cycle or the number of 2-length cycles with additional distances
}

// Runtime: 758ms 
// Memory: 72.94MB